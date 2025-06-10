/**
 * @file	maf_averaging.h
 *
 * @date Dec 11, 2013
 * @author Andrey Belomutskiy, (c) 2012-2020
 */

#pragma once
#include "engine_module.h"
#include "stored_value_sensor.h"
#include "sensor_converter_func.h"
#include "scheduler.h"
#include "table_func.h"




/**
* here we have averaging start and averaging end points for each cylinder
* TODO: migrate to AngleBasedEvent, see also #7869
*/
struct mafSampler {
	scheduling_s startTimer;
	scheduling_s endTimer;
	uint8_t cylinderNumber;
};

#if EFI_MAF_AVERAGING

#if HAL_USE_ADC
void mafAveragingAdcCallback(float instantVoltage);
#endif

// allow smoothing up to number of cylinders
#define MAX_MAF_BUFFER_LENGTH (MAX_CYLINDER_COUNT)
#endif /* EFI_MAF_AVERAGING */

#define SAMPLER_DIMENSION 2

class MafAverager : public StoredValueSensor {
public:
	MafAverager(SensorType type, efidur_t timeout)
		: StoredValueSensor(type, timeout)
	{
	}

	void start(uint8_t cylinderNumber);
	void stop();

	SensorResult submit(float sensorVolts);

	void setFunction(SensorConverter& func) {
		m_function = &func;
	}

	void showInfo(const char* sensorName) const override;

private:
	SensorConverter* m_function = nullptr;

	bool m_isAveraging = false;
	size_t m_counter = 0;
	size_t m_lastCounter = 0;
	float m_sum = 0;
	uint8_t m_cylinderNumber = 0;
};

MafAverager& getMafAvg(size_t idx);
float filterMafValue(float value);

class MafAveragingModule : public EngineModule {
public:
	void onConfigurationChange(engine_configuration_s const * previousConfig) override;

	void onFastCallback() override;
	void triggerCallback(uint32_t index, efitick_t edgeTimestamp);
	void init();
	void submitSample(float voltsMap1, float voltsMap2);
	mafSampler samplers[MAX_CYLINDER_COUNT][SAMPLER_DIMENSION];
};
