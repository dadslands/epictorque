// this section was generated automatically by rusEFI tool config_definition_base-all.jar based on (unknown script) controllers/algo/tps_accel_state.txt
// by class com.rusefi.output.CHeaderConsumer
// begin
#pragma once
#include "rusefi_types.h"
// start of tps_accel_state_s
struct tps_accel_state_s {
	/**
	 * Fuel: TPS AE from
	 * offset 0
	 */
	percent_t tpsFrom = (percent_t)0;
	/**
	 * Fuel: TPS AE to
	 * offset 4
	 */
	percent_t tpsTo = (percent_t)0;
	/**
	 * Fuel: TPS AE change
	 * offset 8
	 */
	percent_t deltaTps = (percent_t)0;
	/**
	 * offset 12
	 */
	floatms_t extraFuel = (floatms_t)0;
	/**
	 * offset 16
	 */
	float valueFromTable = (float)0;
	/**
	 * offset 20
	 */
	float tpsAeCycleMult = (float)0;
	/**
	 * Fuel: TPS AE Active
	offset 24 bit 0 */
	bool isAboveAccelThreshold : 1 {};
	/**
	offset 24 bit 1 */
	bool isBelowDecelThreshold : 1 {};
	/**
	offset 24 bit 2 */
	bool isFractionalEnrichment : 1 {};
	/**
	 * Fuel: TPS AE: below threshold
	offset 24 bit 3 */
	bool belowEpsilon : 1 {};
	/**
	 * Fuel: TPS AE: too short
	offset 24 bit 4 */
	bool tooShort : 1 {};
	/**
	 * Fuel: TPSAE ExtraShot
	offset 24 bit 5 */
	bool extraShot : 1 {};
	/**
	offset 24 bit 6 */
	bool unusedBit_12_6 : 1 {};
	/**
	offset 24 bit 7 */
	bool unusedBit_12_7 : 1 {};
	/**
	offset 24 bit 8 */
	bool unusedBit_12_8 : 1 {};
	/**
	offset 24 bit 9 */
	bool unusedBit_12_9 : 1 {};
	/**
	offset 24 bit 10 */
	bool unusedBit_12_10 : 1 {};
	/**
	offset 24 bit 11 */
	bool unusedBit_12_11 : 1 {};
	/**
	offset 24 bit 12 */
	bool unusedBit_12_12 : 1 {};
	/**
	offset 24 bit 13 */
	bool unusedBit_12_13 : 1 {};
	/**
	offset 24 bit 14 */
	bool unusedBit_12_14 : 1 {};
	/**
	offset 24 bit 15 */
	bool unusedBit_12_15 : 1 {};
	/**
	offset 24 bit 16 */
	bool unusedBit_12_16 : 1 {};
	/**
	offset 24 bit 17 */
	bool unusedBit_12_17 : 1 {};
	/**
	offset 24 bit 18 */
	bool unusedBit_12_18 : 1 {};
	/**
	offset 24 bit 19 */
	bool unusedBit_12_19 : 1 {};
	/**
	offset 24 bit 20 */
	bool unusedBit_12_20 : 1 {};
	/**
	offset 24 bit 21 */
	bool unusedBit_12_21 : 1 {};
	/**
	offset 24 bit 22 */
	bool unusedBit_12_22 : 1 {};
	/**
	offset 24 bit 23 */
	bool unusedBit_12_23 : 1 {};
	/**
	offset 24 bit 24 */
	bool unusedBit_12_24 : 1 {};
	/**
	offset 24 bit 25 */
	bool unusedBit_12_25 : 1 {};
	/**
	offset 24 bit 26 */
	bool unusedBit_12_26 : 1 {};
	/**
	offset 24 bit 27 */
	bool unusedBit_12_27 : 1 {};
	/**
	offset 24 bit 28 */
	bool unusedBit_12_28 : 1 {};
	/**
	offset 24 bit 29 */
	bool unusedBit_12_29 : 1 {};
	/**
	offset 24 bit 30 */
	bool unusedBit_12_30 : 1 {};
	/**
	offset 24 bit 31 */
	bool unusedBit_12_31 : 1 {};
	/**
	 * offset 28
	 */
	uint8_t m_tpsExtraShotTimer = (uint8_t)0;
	/**
	 * need 4 byte alignment
	 * units: units
	 * offset 29
	 */
	uint8_t alignmentFill_at_29[3] = {};
	/**
	 * offset 32
	 */
	float fractionalInjFuel = (float)0;
	/**
	 * offset 36
	 */
	floatms_t accumulatedValue = (floatms_t)0;
	/**
	 * offset 40
	 */
	floatms_t maxExtraPerCycle = (floatms_t)0;
	/**
	 * offset 44
	 */
	floatms_t maxExtraPerPeriod = (floatms_t)0;
	/**
	 * offset 48
	 */
	floatms_t maxInjectedPerPeriod = (floatms_t)0;
	/**
	 * offset 52
	 */
	int cycleCnt = (int)0;
	/**
	 * Fuel: WOT TPS
	 * offset 56
	 */
	percent_t wotTps = (percent_t)0;
	/**
	 * Fuel: TPS AE fromScaled
	 * offset 60
	 */
	percent_t tpsFromScaled = (percent_t)0;
	/**
	 * Fuel: TPS AE toScaled
	 * offset 64
	 */
	percent_t tpsToScaled = (percent_t)0;
	/**
	 * Engine cycles AE duration
	 * offset 68
	 */
	uint8_t tpsAeCycleCnt = (uint8_t)0;
	/**
	 * need 4 byte alignment
	 * units: units
	 * offset 69
	 */
	uint8_t alignmentFill_at_69[3] = {};
	/**
	offset 72 bit 0 */
	bool tpsAeCycleCntWait : 1 {};
	/**
	offset 72 bit 1 */
	bool unusedBit_52_1 : 1 {};
	/**
	offset 72 bit 2 */
	bool unusedBit_52_2 : 1 {};
	/**
	offset 72 bit 3 */
	bool unusedBit_52_3 : 1 {};
	/**
	offset 72 bit 4 */
	bool unusedBit_52_4 : 1 {};
	/**
	offset 72 bit 5 */
	bool unusedBit_52_5 : 1 {};
	/**
	offset 72 bit 6 */
	bool unusedBit_52_6 : 1 {};
	/**
	offset 72 bit 7 */
	bool unusedBit_52_7 : 1 {};
	/**
	offset 72 bit 8 */
	bool unusedBit_52_8 : 1 {};
	/**
	offset 72 bit 9 */
	bool unusedBit_52_9 : 1 {};
	/**
	offset 72 bit 10 */
	bool unusedBit_52_10 : 1 {};
	/**
	offset 72 bit 11 */
	bool unusedBit_52_11 : 1 {};
	/**
	offset 72 bit 12 */
	bool unusedBit_52_12 : 1 {};
	/**
	offset 72 bit 13 */
	bool unusedBit_52_13 : 1 {};
	/**
	offset 72 bit 14 */
	bool unusedBit_52_14 : 1 {};
	/**
	offset 72 bit 15 */
	bool unusedBit_52_15 : 1 {};
	/**
	offset 72 bit 16 */
	bool unusedBit_52_16 : 1 {};
	/**
	offset 72 bit 17 */
	bool unusedBit_52_17 : 1 {};
	/**
	offset 72 bit 18 */
	bool unusedBit_52_18 : 1 {};
	/**
	offset 72 bit 19 */
	bool unusedBit_52_19 : 1 {};
	/**
	offset 72 bit 20 */
	bool unusedBit_52_20 : 1 {};
	/**
	offset 72 bit 21 */
	bool unusedBit_52_21 : 1 {};
	/**
	offset 72 bit 22 */
	bool unusedBit_52_22 : 1 {};
	/**
	offset 72 bit 23 */
	bool unusedBit_52_23 : 1 {};
	/**
	offset 72 bit 24 */
	bool unusedBit_52_24 : 1 {};
	/**
	offset 72 bit 25 */
	bool unusedBit_52_25 : 1 {};
	/**
	offset 72 bit 26 */
	bool unusedBit_52_26 : 1 {};
	/**
	offset 72 bit 27 */
	bool unusedBit_52_27 : 1 {};
	/**
	offset 72 bit 28 */
	bool unusedBit_52_28 : 1 {};
	/**
	offset 72 bit 29 */
	bool unusedBit_52_29 : 1 {};
	/**
	offset 72 bit 30 */
	bool unusedBit_52_30 : 1 {};
	/**
	offset 72 bit 31 */
	bool unusedBit_52_31 : 1 {};
	/**
	 * offset 76
	 */
	float AccelThreshold = (float)0;
	/**
	 * offset 80
	 */
	uint8_t tpsaeburnskip = (uint8_t)0;
	/**
	 * need 4 byte alignment
	 * units: units
	 * offset 81
	 */
	uint8_t alignmentFill_at_81[3] = {};
};
static_assert(sizeof(tps_accel_state_s) == 84);

// end
// this section was generated automatically by rusEFI tool config_definition_base-all.jar based on (unknown script) controllers/algo/tps_accel_state.txt
