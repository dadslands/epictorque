#include "pch.h"

#include "init.h"
#include "adc_subscription.h"
#include "function_pointer_sensor.h"
#include "functional_sensor.h"
#include "live_data.h"
#include "linear_func.h"

static FunctionalSensor lambdaSensor (SensorType::Lambda1 , /* timeout = */ MS2NT(500));
static FunctionalSensor lambdaSensor2(SensorType::Lambda2, /* timeout = */ MS2NT(500));

static LinearFunc afrConverter;

#include "AemXSeriesLambda.h"

// if the sensor is beign configured as an AFR for a particular fuel, SensorType::Lambda# runs internally in lambda always, convert from AFR to lambda using primary Stoich Ratio

void configureAfrFunction(LinearFunc& converter) {

	// we are being given AFR values, not lambda values as a config, calculate lambda for primary fuel from these
	if (!engineConfiguration->afrSensorLambdaRange) {
		converter.configure(
			engineConfiguration->afr.v1,
			engineConfiguration->afr.value1 / engineConfiguration->stoichRatioPrimary,
			engineConfiguration->afr.v2,
			engineConfiguration->afr.value2 / engineConfiguration->stoichRatioPrimary,
			0,
			2
		);
	} else {
		// configs are in lambda, send them on
		converter.configure(
			engineConfiguration->afr.v1,
			engineConfiguration->afr.value1,
			engineConfiguration->afr.v2,
			engineConfiguration->afr.value2,
			0,
			2
		);

	}
}



#if EFI_CAN_SUPPORT
static AemXSeriesWideband aem1(0, SensorType::Lambda1);
static AemXSeriesWideband aem2(1, SensorType::Lambda2);
#endif

template <>
const wideband_state_s* getLiveData(size_t idx) {
#if EFI_CAN_SUPPORT
	switch (idx) {
		case 0:
			aem1.refreshState();
			return &aem1;
		case 1:
			aem2.refreshState();
			return &aem2;
	}
#endif

	return nullptr;
}

void initLambda() {
	if (isAdcChannelValid(engineConfiguration->afr.hwChannel) && engineConfiguration->enableAemXSeries) {
		criticalError("Please pick either analog AFR or CAN AFR input not both.");
	}

#if EFI_CAN_SUPPORT
	if (engineConfiguration->enableAemXSeries) {
		if (!engineConfiguration->canWriteEnabled || !engineConfiguration->canReadEnabled) {
			criticalError("CAN read and write are required to use CAN wideband.");
			return;
		}

		registerCanSensor(aem1);
		registerCanSensor(aem2);

		return;
	}
#endif

#if EFI_UNIT_TEST
  constexpr bool isUnitTest = true;
#else
  constexpr bool isUnitTest = false;
#endif

	configureAfrFunction(afrConverter);

  // CANbus option is handled above, let's handle analog inputs conditionally to give Lua sensors a chance
	if (isAdcChannelValid(engineConfiguration->afr.hwChannel) || isUnitTest) {
		lambdaSensor.setFunction(afrConverter);
		AdcSubscription::SubscribeSensor(lambdaSensor, engineConfiguration->afr.hwChannel, config->egoLowPassCutoffHz == 0?100:config->egoLowPassCutoffHz);
		lambdaSensor.Register();
	}
	if (isAdcChannelValid(engineConfiguration->afr.hwChannel2) || isUnitTest) {
		lambdaSensor2.setFunction(afrConverter);
		AdcSubscription::SubscribeSensor(lambdaSensor2, engineConfiguration->afr.hwChannel2, config->egoLowPassCutoffHz == 0?100:config->egoLowPassCutoffHz);
		lambdaSensor2.Register();
	}
}

void deinitLambda() {
	if (engineConfiguration->enableAemXSeries) {
		return;
	}

#if EFI_UNIT_TEST
	constexpr bool isUnitTest = true;
#else
	constexpr bool isUnitTest = false;
#endif

	if (isAdcChannelValid(engineConfiguration->afr.hwChannel) || isUnitTest) {
		AdcSubscription::UnsubscribeSensor(lambdaSensor, engineConfiguration->afr.hwChannel);
		lambdaSensor.unregister();
	}

	if (isAdcChannelValid(engineConfiguration->afr.hwChannel2) || isUnitTest) {
		lambdaSensor2.setFunction(afrConverter);
		AdcSubscription::UnsubscribeSensor(lambdaSensor2, engineConfiguration->afr.hwChannel2);
		lambdaSensor2.unregister();
	}
}
