/**
* @file	map_averaging.cpp
 *
 * In order to have best MAP estimate possible, we real MAP value at a relatively high frequency
 * and average the value within a specified angle position window for each cylinder
 *
 * @date Dec 11, 2013
 * @author Andrey Belomutskiy, (c) 2012-2020
 *
 * This file is part of rusEfi - see http://rusefi.com
 *
 * rusEfi is free software; you can redistribute it and/or modify it under the terms of
 * the GNU General Public License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * rusEfi is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without
 * even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with this program.
 * If not, see <http://www.gnu.org/licenses/>.
 */

#include "pch.h"
#include "exp_average.h"


#if EFI_MAF_AVERAGING && defined (MODULE_MAF_AVERAGING)
#if !EFI_SHAFT_POSITION_INPUT
	fail("EFI_SHAFT_POSITION_INPUT required to have EFI_EMULATE_POSITION_SENSORS")
#endif // EFI_SHAFT_POSITION_INPUT

#include "maf_averaging.h"
#include "trigger_central.h"


/**
 * this instance does not have a real physical pin - it's only used for engine sniffer
 *
 * todo: we can kind of add real physical pin just for a very narrow case of troubleshooting but only if we ever need it :)
 */
static NamedOutputPin mafAveragingPin("maf");

// allow smoothing up to number of cylinders
#define MAX_MAF_BUFFER_LENGTH (MAX_CYLINDER_COUNT)
// in MAF units, not voltage!
static float averagedMafRunningBuffer[MAX_MAF_BUFFER_LENGTH];
static int mafMinBufferLength = 0;
static int averagedMafBufIdx = 0;


static void endAveraging(MafAverager* arg);

static size_t currentMafAverager = 0;

void startMafAveraging(mafSampler* s) {
	efiAssertVoid(ObdCode::CUSTOM_ERR_6649, hasLotsOfRemainingStack(), "lowstck#9");

	// TODO: set currentMafAverager based on cylinder bank
	auto& averager = getMafAvg(currentMafAverager);
	averager.start(s->cylinderNumber);

	mafAveragingPin.setHigh();
	engine->outputChannels.isMafAveraging = true;

	scheduleByAngle(&s->endTimer, getTimeNowNt(), engine->engineState.mafAveragingDuration,
		{ endAveraging, &averager });
}

void MafAverager::start(uint8_t cylinderNumber) {
	chibios_rt::CriticalSectionLocker csl;

	m_counter = 0;
	m_sum = 0;
	m_isAveraging = true;
	m_cylinderNumber = cylinderNumber;
}

SensorResult MafAverager::submit(float volts) {
	auto result = m_function ? m_function->convert(volts) : unexpected;

	if (m_isAveraging && result) {
		chibios_rt::CriticalSectionLocker csl;

		m_counter++;
		m_sum += result.Value;
	}

	return result;
}

static ExpAverage expAverageMaf;


// huh? why is this killing unit tests _linking_ only on WINDOWS?! PUBLIC_API_WEAK
float filterMafValue(float value) {
  expAverageMaf.setSmoothingFactor(engineConfiguration->mafExpAverageAlpha);
  return expAverageMaf.initOrAverage(value);
}

void MafAverager::stop() {
	chibios_rt::CriticalSectionLocker csl;

	m_isAveraging = false;

	if (m_counter > 0) {
		float averageMaf = m_sum / m_counter;
		m_lastCounter = m_counter;

		// TODO: this should be per-sensor, not one for all MAF sensors
		averagedMafRunningBuffer[averagedMafBufIdx] = averageMaf;
		// increment circular running buffer index
		averagedMafBufIdx = (averagedMafBufIdx + 1) % mafMinBufferLength;
		// find min. value (only works for flow values, not raw voltages!)
		float minFlow = averagedMafRunningBuffer[0];
		for (int i = 1; i < mafMinBufferLength; i++) {
			if (averagedMafRunningBuffer[i] < minFlow)
				minFlow = averagedMafRunningBuffer[i];
		}
		engine->outputChannels.mafPerCylinder[m_cylinderNumber] = minFlow;
		setValidValue(filterMafValue(minFlow), getTimeNowNt());
	} else {
#if EFI_PROD_CODE
		warning(ObdCode::CUSTOM_UNEXPECTED_MAF_VALUE, "No MAF values to average");
#endif
	}
}


#if HAL_USE_ADC

/**
 * This method is invoked from ADC callback.
 * @note This method is invoked OFTEN, this method is a potential bottleneck - the implementation should be
 * as fast as possible
 */
void mafAveragingAdcCallback(float instantVoltage) {
	efiAssertVoid(ObdCode::CUSTOM_ERR_6650, hasLotsOfRemainingStack(), "lowstck#9a");

	SensorResult mafResult = getMafAvg(currentMafAverager).submit(instantVoltage);

	if (!mafResult) {
		// hopefully this warning is not too much CPU consumption for fast ADC callback
		warning(ObdCode::CUSTOM_INSTANT_MAF_DECODING, "Invalid MAF at %f", instantVoltage);
		engine->outputChannels.isMafValid = false;
	} else {
		engine->outputChannels.isMafValid = true;
	}

#if EFI_TUNER_STUDIO
	float instantMaf = mafResult.value_or(0);
	engine->outputChannels.instantMAFValue = instantMaf;
#endif // EFI_TUNER_STUDIO
}


#endif

static void endAveraging(MafAverager* arg) {
	arg->stop();

	engine->outputChannels.isMafAveraging = false;
	mafAveragingPin.setLow();
}

static void applyMafMinBufferLength() {
	// check range
	mafMinBufferLength = maxI(minI(engineConfiguration->mafMinBufferLength, MAX_MAF_BUFFER_LENGTH), 1);
	// reset index
	averagedMafBufIdx = 0;
	// fill with maximum values
	for (int i = 0; i < mafMinBufferLength; i++) {
		averagedMafRunningBuffer[i] = FLT_MAX;
	}
}

void MafAveragingModule::onFastCallback() {
	float rpm = Sensor::getOrZero(SensorType::Rpm);
	if (isValidRpm(rpm)) { // we share the configs with map sensor
		MAP_sensor_config_s * c = &engineConfiguration->map;
		angle_t start = interpolate2d(rpm, c->samplingAngleBins, c->samplingAngle);
		efiAssertVoid(ObdCode::CUSTOM_ERR_MAF_START_ASSERT, !std::isnan(start), "start");

		angle_t offsetAngle = engine->triggerCentral.triggerFormDetails.eventAngles[0];
		efiAssertVoid(ObdCode::CUSTOM_ERR_MAF_AVG_OFFSET, !std::isnan(offsetAngle), "offsetAngle");

		for (size_t i = 0; i < engineConfiguration->cylindersCount; i++) {
		  // todo: potential micro-optimization to reuse getEngineState()->engineCycle?
			angle_t cylinderOffset = getEngineCycle(getEngineRotationState()->getOperationMode()) * i / engineConfiguration->cylindersCount;
			efiAssertVoid(ObdCode::CUSTOM_ERR_MAF_CYL_OFFSET, !std::isnan(cylinderOffset), "cylinderOffset");
			// part of this formula related to specific cylinder offset is never changing - we can
			// move the loop into start-up calculation and not have this loop as part of periodic calculation
			// todo: change the logic as described above in order to reduce periodic CPU usage?
			float cylinderStart = start + cylinderOffset - offsetAngle + tdcPosition();
			wrapAngle(cylinderStart, "cylinderStart", ObdCode::CUSTOM_ERR_6562);
			engine->engineState.mafAveragingStart[i] = cylinderStart;
		}
		engine->engineState.mafAveragingDuration = interpolate2d(rpm, c->samplingWindowBins, c->samplingWindow);
	} else {
		for (size_t i = 0; i < engineConfiguration->cylindersCount; i++) {
			engine->engineState.mafAveragingStart[i] = NAN;
		}
		engine->engineState.mafAveragingDuration = NAN;
	}
}

void MafAveragingModule::onConfigurationChange(engine_configuration_s const * previousConfig) {
	if (!previousConfig || engineConfiguration->mafMinBufferLength != previousConfig->mafMinBufferLength) {
		applyMafMinBufferLength();
	}
}

void MafAveragingModule::init() {
	for (size_t structIndex = 0;structIndex < SAMPLER_DIMENSION;structIndex++) {
		for (size_t cylinderIndex = 0; cylinderIndex < MAX_CYLINDER_COUNT; cylinderIndex++) {
			samplers[cylinderIndex][structIndex].cylinderNumber = cylinderIndex;
		}
	}
	if (engineConfiguration->isMafAveragingEnabled) {
		efiPrintf("initMafAveraging...");
		applyMafMinBufferLength();
	} else {
		efiPrintf("Running without MafAveraging...");
	}
}

/**
 * Shaft Position callback used to schedule start and end of MAF averaging
 */
void MafAveragingModule::triggerCallback(uint32_t index, efitick_t edgeTimestamp) {
  	if (!engineConfiguration->isMafAveragingEnabled){
    	return;
  	}
	// update only once per engine cycle
	if (index != 0) {
		return;
	}

	float rpm = Sensor::getOrZero(SensorType::Rpm);
	if (!isValidRpm(rpm)) {
		return;
	}

	ScopePerf perf(PE::MafAveragingTriggerCallback);

	if (engineConfiguration->mafMinBufferLength != mafMinBufferLength) {
		applyMafMinBufferLength();
	}

	// todo: this could be pre-calculated
	int samplingCount = engineConfiguration->measureMafOnlyInOneCylinder ? 1 : engineConfiguration->cylindersCount;

	for (int i = 0; i < samplingCount; i++) {
		angle_t samplingStart = engine->engineState.mafAveragingStart[i];

		angle_t samplingDuration = engine->engineState.mafAveragingDuration;
		// todo: this assertion could be moved out of trigger handler
		assertAngleRange(samplingDuration, "samplingDuration", ObdCode::CUSTOM_ERR_6563);
		if (samplingDuration <= 0) {
			warning(ObdCode::CUSTOM_MAF_ANGLE_PARAM, "maf sampling angle should be positive");
			return;
		}

		angle_t samplingEnd = samplingStart + samplingDuration;

		if (std::isnan(samplingEnd)) {
			// todo: when would this happen?
			warning(ObdCode::CUSTOM_ERR_6549, "no maf angles");
			return;
		}

		// todo: pre-calculate samplingEnd for each cylinder
		wrapAngle(samplingEnd, "samplingEnd", ObdCode::CUSTOM_ERR_6563);
		// only if value is already prepared
		int structIndex = getRevolutionCounter() % SAMPLER_DIMENSION;

		auto & mafAveraging = *engine->module<MafAveragingModule>();
		mafSampler* s = &mafAveraging.samplers[i][structIndex];

		// at the moment we schedule based on time prediction based on current RPM and angle
		// we are loosing precision in case of changing RPM - the further away is the event the worse is precision
		// todo: schedule this based on closest trigger event, same as ignition works
		scheduleByAngle(&s->startTimer, edgeTimestamp, samplingStart,
				{ startMafAveraging, s });
	}
}

#else
void MafAveragingModule::onFastCallback(){}
void MafAveragingModule::onConfigurationChange(engine_configuration_s const *){}
void MafAveragingModule::init() {}
void MafAveragingModule::triggerCallback(uint32_t, efitick_t){}
#endif /* EFI_MAF_AVERAGING */
