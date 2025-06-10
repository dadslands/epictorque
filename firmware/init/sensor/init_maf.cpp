#include "pch.h"

#include "init.h"
#include "adc_subscription.h"
#include "fallback_sensor.h"
#include "functional_sensor.h"
#include "table_func.h"
#include "maf_averaging.h"

static FunctionalSensor slowMafSensor (SensorType::MafSlow , MS2NT(50));
static FunctionalSensor slowMafSensor2 (SensorType::MafSlow2 ,  MS2NT(50));

static MafAverager fastMafSensor(SensorType::MafFast, MS2NT(200));
static MafAverager fastMafSensor2(SensorType::MafFast2, MS2NT(200));


static FallbackSensor mafCombiner(SensorType::Maf, SensorType::MafFast, SensorType::MafSlow);
static FallbackSensor mafCombiner2(SensorType::Maf2, SensorType::MafFast2, SensorType::MafSlow2);

// extract the type of the elements in the bin/value arrays
using BinType = std::remove_extent_t<decltype(config->mafDecodingBins)>;
using ValueType = std::remove_extent_t<decltype(config->mafDecoding)>;

// This function converts volts -> kg/h
static TableFunc mafCurve(config->mafDecodingBins, config->mafDecoding);


MafAverager& getMafAvg(size_t cylinderBankIndex) {
	(void) cylinderBankIndex;

	return cylinderBankIndex == 0 ? fastMafSensor : fastMafSensor2;
}


static void initMaf(adc_channel_e channel, FunctionalSensor& m, MafAverager& mavg) {
 	if (!isAdcChannelValid(channel)) {
 		return;
 	}

 	m.setFunction(mafCurve);
 	mavg.setFunction(mafCurve);

 	AdcSubscription::SubscribeSensor(m, channel, config->mafLowPassCutoffHz == 0?50:config->mafLowPassCutoffHz);
 	m.Register();
 	if (!engineConfiguration->noFastMaf) {
 		mavg.Register();
 	}
}

void initMaf() {
	initMaf(engineConfiguration->mafAdcChannel, slowMafSensor, fastMafSensor);
	initMaf(engineConfiguration->maf2AdcChannel, slowMafSensor2, fastMafSensor2);
	mafCombiner.Register();
	mafCombiner2.Register();
}

void deinitMaf() {
	AdcSubscription::UnsubscribeSensor(slowMafSensor, engineConfiguration->mafAdcChannel);
	AdcSubscription::UnsubscribeSensor(slowMafSensor2, engineConfiguration->maf2AdcChannel);
}