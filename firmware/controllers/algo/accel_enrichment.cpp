/**
 * @file    accel_enrichment.cpp
 * @brief   Acceleration enrichment calculator
 *
 * In this file we have three strategies for acceleration/deceleration fuel correction
 *
 * 1) MAP rate-of-change correction
 * 2) TPS rate-of-change correction
 * 3) fuel film/wal wetting correction
 *   AWC Added to Wall Coefficient, %
 *   AWA Added to Wall Amount
 *   SOC Sucked Off wall Coefficient, %
 *   SOA Sucked Off wall amount
 *   WF  current on-Wall Fuel amount
 *
 *
 * http://rusefi.com/wiki/index.php?title=Manual:Software:Fuel_Control
 * @date Apr 21, 2014
 * @author Dmitry Sidin
 * @author Andrey Belomutskiy, (c) 2012-2020
 * @author Matthew Kennedy
 */

#include "pch.h"
#include "accel_enrichment.h"

// static tps_tps_Map3D_t tpsTpsMap{"tps"};

// on this level we do not distinguish between multiplier and 'ms adder' modes
float TpsAccelEnrichment::getTpsEnrichment() {
	ScopePerf perf(PE::GetTpsEnrichment);

	if (engineConfiguration->tpsAccelAeEnabled == 0) {
		// explicit toggle of tps AE - tpsAccelLookback is used for mapPrediction
		return 0;
	}
	float rpm = Sensor::getOrZero(SensorType::Rpm);
	if (rpm == 0) {
		return 0;
	}

	wotTps = clampF( 0, interpolate2d(rpm, config->wotTpsRpmBins, config->wotTpsValues), 100);
	if (wotTps <= 0) { // 0 disables scaling
		wotTps = 100;
	}

	if (tpsAeCycleCnt >= config->tpsAeCycleCycleBins[TPS_AE_MAP-1]) {
		extraFuel = 0;
	} else {
		extraFuel = interpolate3d(config->tpsAeCycleValues,
					config->tpsAeCycleTpsToBins, tpsToScaled,
					config->tpsAeCycleCycleBins,  tpsAeCycleCnt);
	}

	float mult = interpolate2d(rpm, config->tpsTspCorrValuesBins, config->tpsTspCorrValues);
	if (mult != 0 && (mult < 0.01 || mult > 100)) {
		mult = 1;
	}

	return extraFuel * mult;
}

void TpsAccelEnrichment::onEngineCycleTps() {
	// we update values in handleFuel() directly by calling onNewValue()
	// decrement extraShotTimer every cycle so we don't trigger more than one
	if (m_tpsExtraShotTimer > 0) {
		m_tpsExtraShotTimer--;
	}

	// increment AeCycleCnt able X axis for decay
	if (tpsAeCycleCnt < 250) {
			tpsAeCycleCnt++;
	}

}

int TpsAccelEnrichment::getMaxDeltaIndex() {
	int len = minI(cb.getSize(), cb.getCount());
	tooShort = len < 2;
	if (tooShort)
		return 0;
	int ci = cb.currentIndex - 1;
	float maxValue = cb.get(ci) - cb.get(ci - 1);
	int resultIndex = ci;

	// todo: 'get' method is maybe a bit heavy because of the branching
	// todo: this could be optimized with some careful magic

	for (int i = 1; i<len - 1;i++) {
		float v = cb.get(ci - i) - cb.get(ci - i - 1);
		if (v > maxValue) {
			maxValue = v;
			resultIndex = ci - i;
		}
	}

	return resultIndex;
}

float TpsAccelEnrichment::getMaxDelta() {
	int index = getMaxDeltaIndex();

	return (cb.get(index) - (cb.get(index - 1)));
}

void TpsAccelEnrichment::resetAE() {
	cb.clear();
}

void TpsAccelEnrichment::setLength(int length) {
	cb.setSize(length);
}

void TpsAccelEnrichment::onNewValue(float currentValue) {
	// Push new value in to the history buffer
	//	cb.add(currentValue);

    wotTps = clampF( 0, interpolate2d(Sensor::getOrZero(SensorType::Rpm), config->wotTpsRpmBins, config->wotTpsValues), 100);
	if (wotTps <= 0) { // 0 disables scaling
		wotTps = 100;
	}

	// scaled TPS
	if (engineConfiguration->tpsAeScaledFrom) {
		cb.add(clampF(0, (100.0/wotTps) * currentValue ,  100));
	} else {
		cb.add(currentValue);
	}
	// Update deltas
	int maxDeltaIndex = getMaxDeltaIndex();
	// we just get the numbers, they should be scaled already
	tpsFrom = cb.get(maxDeltaIndex - 1);
	tpsTo = cb.get(maxDeltaIndex);
	// if (engineConfiguration->tpsAeScaledFrom) {
	// 	tpsFromScaled = clampF(0, (100.0/wotTps) * tpsFrom ,  100);
	// } else {
	// 	tpsFromScaled = tpsFrom;
	// }
	// tpsToScaled =   clampF(0, (100.0/wotTps) * tpsTo    , 100);

	tpsFromScaled = tpsFrom;
	tpsToScaled = tpsTo;


	// Update threshold detection
	if (tpsaeburnskip > 0) {
		isAboveAccelThreshold = 0;
		deltaTps = 0;
		tpsaeburnskip--;
		return;
	}

	deltaTps = tpsToScaled - tpsFromScaled;
	if (Sensor::getOrZero(SensorType::Rpm) <  engineConfiguration->cranking.rpm) {
		deltaTps = 0;
	}


	AccelThreshold = interpolate2d(Sensor::getOrZero(SensorType::Rpm), config->tpsAeThresholdRpmBins, config->tpsAeThresholdValue);
	isAboveAccelThreshold = deltaTps > AccelThreshold;
	if (isAboveAccelThreshold && cb.getCount() > CB_MAX_SIZE) {
		tpsAeCycleCnt = 0;
		if (engineConfiguration->tpsAccelExtraShot) {
			extraAccel_shot();
		}
	}
	// TODO: can deltaTps actually be negative? Will this ever trigger?
	isBelowDecelThreshold = deltaTps < -engineConfiguration->tpsDecelEnleanmentThreshold;
}

TpsAccelEnrichment::TpsAccelEnrichment() {
	resetAE();
	cb.setSize(4);
	m_tpsExtraShotTimer = config->tpsExtraShotTimer;
	cb.add(Sensor::getOrZero(SensorType::Tps1));
	cb.add(Sensor::getOrZero(SensorType::Tps1));

}

void TpsAccelEnrichment::onConfigurationChange(engine_configuration_s const* /*previousConfig*/) {
	float periodms;
	if (engineConfiguration->tpsAeFastCallback) {
		periodms = FAST_CALLBACK_PERIOD_MS;
	} else {
		periodms = SLOW_CALLBACK_PERIOD_MS;
	}

	m_tpsExtraShotTimer = config->tpsExtraShotTimer;

	int length = engineConfiguration->tpsAccelLookback / (periodms / 1000.0f);;

	if (length < 1) {
		efiPrintf("setTpsAccelLen: Length should be positive [%d]", length);
		return;
	}

	setLength(length);
	cb.add(Sensor::getOrZero(SensorType::Tps1));
	cb.add(Sensor::getOrZero(SensorType::Tps1));
	cb.add(Sensor::getOrZero(SensorType::Tps1));
	cb.add(Sensor::getOrZero(SensorType::Tps1));
	cb.add(Sensor::getOrZero(SensorType::Tps1));
}

void initAccelEnrichment() {
	engine->module<TpsAccelEnrichment>()->onConfigurationChange(nullptr);
}


void TpsAccelEnrichment::extraAccelShot_stop(void *arg) {
	(void)arg;
	endSimultaneousInjectionOnlyTogglePins();
}

void TpsAccelEnrichment::extraAccelShot_start(void *arg) {
	(void)arg;
	getScheduler()->schedule("extraShot", nullptr, getTimeNowNt() + MSF2NT(engine->engineState.injectionDuration * config->tpsExtraShotMult),  &extraAccelShot_stop);
	startSimultaneousInjection();
}

void TpsAccelEnrichment::extraAccel_shot(void) {
	if (m_tpsExtraShotTimer) {
		return;
	}

	m_tpsExtraShotTimer = config->tpsExtraShotTimer;
	auto startTime = getTimeNowNt() + 1;
	getScheduler()->schedule("extraShot", nullptr, startTime,  &extraAccelShot_start);

}
