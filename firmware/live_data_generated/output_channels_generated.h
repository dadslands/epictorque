// this section was generated automatically by rusEFI tool config_definition_base-all.jar based on (unknown script) console/binary/output_channels.txt
// by class com.rusefi.output.CHeaderConsumer
// begin
#pragma once
#include "rusefi_types.h"
// start of pid_status_s
struct pid_status_s {
	/**
	 * offset 0
	 */
	float pTerm = (float)0;
	/**
	 * offset 4
	 */
	scaled_channel<int16_t, 100, 1> iTerm = (int16_t)0;
	/**
	 * offset 6
	 */
	scaled_channel<int16_t, 100, 1> dTerm = (int16_t)0;
	/**
	 * offset 8
	 */
	scaled_channel<int16_t, 100, 1> output = (int16_t)0;
	/**
	 * offset 10
	 */
	scaled_channel<int16_t, 100, 1> error = (int16_t)0;
	/**
	 * offset 12
	 */
	uint32_t resetCounter = (uint32_t)0;
};
static_assert(sizeof(pid_status_s) == 16);

// start of output_channels_s
struct output_channels_s {
	/**
	 * SD: Present
	offset 0 bit 0 */
	bool sd_present : 1 {};
	/**
	 * SD: Logging
	offset 0 bit 1 */
	bool sd_logging_internal : 1 {};
	/**
	offset 0 bit 2 */
	bool triggerScopeReady : 1 {};
	/**
	offset 0 bit 3 */
	bool antilagTriggered : 1 {};
	/**
	offset 0 bit 4 */
	bool isO2HeaterOn : 1 {};
	/**
	offset 0 bit 5 */
	bool checkEngine : 1 {};
	/**
	offset 0 bit 6 */
	bool needBurn : 1 {};
	/**
	 * SD: MSD
	offset 0 bit 7 */
	bool sd_msd : 1 {};
	/**
	 * Tooth Logger Ready
	offset 0 bit 8 */
	bool toothLogReady : 1 {};
	/**
	 * Error: TPS
	offset 0 bit 9 */
	bool isTpsError : 1 {};
	/**
	 * Error: CLT
	offset 0 bit 10 */
	bool isCltError : 1 {};
	/**
	 * Error: MAP
	offset 0 bit 11 */
	bool isMapError : 1 {};
	/**
	 * Error: IAT
	offset 0 bit 12 */
	bool isIatError : 1 {};
	/**
	 * Error: Trigger
	offset 0 bit 13 */
	bool isTriggerError : 1 {};
	/**
	 * Error: Active
	offset 0 bit 14 */
	bool hasCriticalError : 1 {};
	/**
	 * Warning: Active
	offset 0 bit 15 */
	bool isWarnNow : 1 {};
	/**
	 * Error: Pedal
	offset 0 bit 16 */
	bool isPedalError : 1 {};
	/**
	 * Launch Control Triggered
	offset 0 bit 17 */
	bool launchTriggered : 1 {};
	/**
	 * Error: TPS2
	offset 0 bit 18 */
	bool isTps2Error : 1 {};
	/**
	 * Injector Fault
	offset 0 bit 19 */
	bool injectorFault : 1 {};
	/**
	 * Ignition Fault
	offset 0 bit 20 */
	bool ignitionFault : 1 {};
	/**
	 * isUsbConnected
	 * Original reason for this is to check if USB is connected from Lua
	offset 0 bit 21 */
	bool isUsbConnected : 1 {};
	/**
	offset 0 bit 22 */
	bool dfcoActive : 1 {};
	/**
	 * SD card writing
	offset 0 bit 23 */
	bool sd_active_wr : 1 {};
	/**
	 * SD card reading
	offset 0 bit 24 */
	bool sd_active_rd : 1 {};
	/**
	 * MAP from sensor seems valid
	offset 0 bit 25 */
	bool isMapValid : 1 {};
	/**
	offset 0 bit 26 */
	bool triggerPageRefreshFlag : 1 {};
	/**
	offset 0 bit 27 */
	bool hasFaultReportFile : 1 {};
	/**
	 * Analog sensors supply failure
	offset 0 bit 28 */
	bool isAnalogFailure : 1 {};
	/**
	offset 0 bit 29 */
	bool isTuningNow : 1 {};
	/**
	 * SD: formating is in progress
	offset 0 bit 30 */
	bool sd_formating : 1 {};
	/**
	offset 0 bit 31 */
	bool isMapAveraging : 1 {};
	/**
	 * @@GAUGE_NAME_RPM@@
	 * units: RPM
	 * offset 4
	 */
	uint16_t RPMValue = (uint16_t)0;
	/**
	 * dRPM
	 * units: RPM acceleration/Rate of Change/ROC
	 * offset 6
	 */
	int16_t rpmAcceleration = (int16_t)0;
	/**
	 * @@GAUGE_NAME_GEAR_RATIO@@
	 * units: value
	 * offset 8
	 */
	scaled_channel<uint16_t, 200, 1> speedToRpmRatio = (uint16_t)0;
	/**
	 * @@GAUGE_NAME_VVS@@
	 * units: kph
	 * offset 10
	 */
	uint8_t unusedVehicleSpeedKph = (uint8_t)0;
	/**
	 * @@GAUGE_NAME_CPU_TEMP@@
	 * units: deg C
	 * offset 11
	 */
	int8_t internalMcuTemperature = (int8_t)0;
	/**
	 * @@GAUGE_NAME_CLT@@
	 * units: deg C
	 * offset 12
	 */
	scaled_channel<int16_t, 100, 1> coolant = (int16_t)0;
	/**
	 * @@GAUGE_NAME_IAT@@
	 * units: deg C
	 * offset 14
	 */
	scaled_channel<int16_t, 100, 1> intake = (int16_t)0;
	/**
	 * units: deg C
	 * offset 16
	 */
	scaled_channel<int16_t, 100, 1> auxTemp1 = (int16_t)0;
	/**
	 * units: deg C
	 * offset 18
	 */
	scaled_channel<int16_t, 100, 1> auxTemp2 = (int16_t)0;
	/**
	 * @@GAUGE_NAME_TPS@@
	 * units: %
	 * offset 20
	 */
	scaled_channel<int16_t, 200, 1> TPSValue = (int16_t)0;
	/**
	 * @@GAUGE_NAME_THROTTLE_PEDAL@@
	 * units: %
	 * offset 22
	 */
	scaled_channel<int16_t, 200, 1> throttlePedalPosition = (int16_t)0;
	/**
	 * units: ADC
	 * offset 24
	 */
	uint16_t tpsADC = (uint16_t)0;
	/**
	 * units: ADC
	 * offset 26
	 */
	uint16_t tpsSecondaryADC = (uint16_t)0;
	/**
	 * units: V
	 * offset 28
	 */
	scaled_channel<uint16_t, 12000, 1> rawMaf = (uint16_t)0;
	/**
	 * @@GAUGE_NAME_AIR_FLOW_MEASURED@@
	 * units: kg/h
	 * offset 30
	 */
	scaled_channel<uint16_t, 25, 1> mafMeasured = (uint16_t)0;
	/**
	 * @@GAUGE_NAME_MAP@@
	 * units: kPa
	 * offset 32
	 */
	scaled_channel<uint16_t, 100, 1> MAPValue = (uint16_t)0;
	/**
	 * units: kPa
	 * offset 34
	 */
	scaled_channel<uint16_t, 500, 1> baroPressure = (uint16_t)0;
	/**
	 * @@GAUGE_NAME_LAMBDA@@
	 * offset 36
	 */
	scaled_channel<uint16_t, 10000, 1> lambdaValue = (uint16_t)0;
	/**
	 * @@GAUGE_NAME_VBAT@@
	 * units: V
	 * offset 38
	 */
	scaled_channel<uint16_t, 3000, 1> VBatt = (uint16_t)0;
	/**
	 * @@GAUGE_NAME_OIL_PRESSURE@@
	 * units: kPa
	 * offset 40
	 */
	scaled_channel<uint16_t, 30, 1> oilPressure = (uint16_t)0;
	/**
	 * @@GAUGE_NAME_VVT_B1I@@
	 * units: deg
	 * offset 42
	 */
	scaled_channel<int16_t, 50, 1> vvtPositionB1I = (int16_t)0;
	/**
	 * @@GAUGE_NAME_FUEL_LAST_INJECTION@@
	 * Actual last injection time - including all compensation and injection mode
	 * units: ms
	 * offset 44
	 */
	scaled_channel<uint16_t, 300, 1> actualLastInjection = (uint16_t)0;
	/**
	 * Actual Injection before Small PW
	 * units: ms
	 * offset 46
	 */
	scaled_channel<uint16_t, 300, 1> actualLastInjPreSmallPw = (uint16_t)0;
	/**
	 * offset 48
	 */
	uint8_t stopEngineCode = (uint8_t)0;
	/**
	 * @@GAUGE_NAME_FUEL_INJ_DUTY@@
	 * units: %
	 * offset 49
	 */
	scaled_channel<uint8_t, 2, 1> injectorDutyCycle = (uint8_t)0;
	/**
	 * @@GAUGE_NAME_FUEL_INJECTION_TIMING@@
	 * units: deg
	 * offset 50
	 */
	int16_t injectionOffset = (int16_t)0;
	/**
	 * @@GAUGE_NAME_ENGINE_CRC16@@
	 * units: crc16
	 * offset 52
	 */
	uint16_t engineMakeCodeNameCrc16 = (uint16_t)0;
	/**
	 * @@GAUGE_NAME_FUEL_WALL_AMOUNT@@
	 * units: mg
	 * offset 54
	 */
	scaled_channel<uint16_t, 100, 1> wallFuelAmount = (uint16_t)0;
	/**
	 * @@GAUGE_NAME_FUEL_WALL_CORRECTION@@
	 * units: mg
	 * offset 56
	 */
	scaled_channel<int16_t, 100, 1> wallFuelCorrectionValue = (int16_t)0;
	/**
	 * offset 58
	 */
	uint16_t revolutionCounterSinceStart = (uint16_t)0;
	/**
	 * @@GAUGE_NAME_CAN_READ_OK@@
	 * offset 60
	 */
	uint16_t canReadCounter = (uint16_t)0;
	/**
	 * @@GAUGE_NAME_FUEL_TPS_EXTRA@@
	 * units: ms
	 * offset 62
	 */
	scaled_channel<int16_t, 300, 1> tpsAccelFuel = (int16_t)0;
	/**
	 * @@GAUGE_NAME_IGNITION_MODE@@
	 * offset 64
	 */
	uint8_t currentIgnitionMode = (uint8_t)0;
	/**
	 * @@GAUGE_NAME_INJECTION_MODE@@
	 * offset 65
	 */
	uint8_t currentInjectionMode = (uint8_t)0;
	/**
	 * @@GAUGE_NAME_DWELL_DUTY@@
	 * units: %
	 * offset 66
	 */
	scaled_channel<uint16_t, 200, 1> coilDutyCycle = (uint16_t)0;
	/**
	 * Spark Dwell Clamp
	 * units: ms
	 * offset 68
	 */
	floatms_t sparkDwellClamp = (floatms_t)0;
	/**
	 * @@GAUGE_NAME_ETB_DUTY@@
	 * units: %
	 * offset 72
	 */
	scaled_channel<int16_t, 200, 1> etb1DutyCycle = (int16_t)0;
	/**
	 * Fuel level
	 * units: %
	 * offset 74
	 */
	scaled_channel<int16_t, 200, 1> fuelTankLevel = (int16_t)0;
	/**
	 * @@GAUGE_NAME_FUEL_CONSUMPTION@@
	 * units: grams
	 * offset 76
	 */
	uint16_t totalFuelConsumption = (uint16_t)0;
	/**
	 * @@GAUGE_NAME_FUEL_FLOW@@
	 * units: gram/s
	 * offset 78
	 */
	scaled_channel<uint16_t, 400, 1> fuelFlowRate = (uint16_t)0;
	/**
	 * @@GAUGE_NAME_TPS2@@
	 * units: %
	 * offset 80
	 */
	scaled_channel<int16_t, 200, 1> TPS2Value = (int16_t)0;
	/**
	 * @@GAUGE_NAME_TUNE_CRC16@@
	 * units: crc16
	 * offset 82
	 */
	uint16_t tuneCrc16 = (uint16_t)0;
	/**
	 * @@GAUGE_NAME_FUEL_VE@@
	 * units: ratio
	 * offset 84
	 */
	scaled_channel<uint16_t, 100, 1> veValue = (uint16_t)0;
	/**
	 * "tunedVE"
	 * units: ratio
	 * offset 86
	 */
	scaled_channel<uint16_t, 100, 1> tunedVeValue = (uint16_t)0;
	/**
	 * "tunedMafCorrection"
	 * units: ratio
	 * offset 88
	 */
	scaled_channel<uint16_t, 100, 1> tunedMafCorrection = (uint16_t)0;
	/**
	 * need 4 byte alignment
	 * units: units
	 * offset 90
	 */
	uint8_t alignmentFill_at_90[2] = {};
	/**
	 * @@GAUGE_NAME_UPTIME@@
	 * units: sec
	 * offset 92
	 */
	uint32_t seconds = (uint32_t)0;
	/**
	 * Engine Mode
	 * units: em
	 * offset 96
	 */
	uint32_t engineMode = (uint32_t)0;
	/**
	 * @@GAUGE_NAME_VERSION@@
	 * units: version_f
	 * offset 100
	 */
	uint32_t firmwareVersion = (uint32_t)0;
	/**
	 * units: V
	 * offset 104
	 */
	scaled_channel<uint16_t, 12000, 1> rawIdlePositionSensor = (uint16_t)0;
	/**
	 * units: V
	 * offset 106
	 */
	scaled_channel<uint16_t, 12000, 1> rawWastegatePosition = (uint16_t)0;
	/**
	 * @@GAUGE_NAME_ACCEL_LAT@@
	 * units: G
	 * offset 108
	 */
	float accelerationLat = (float)0;
	/**
	 * @@GAUGE_NAME_ACCEL_LON@@
	 * units: G
	 * offset 112
	 */
	float accelerationLon = (float)0;
	/**
	 * @@GAUGE_NAME_DETECTED_GEAR@@
	 * offset 116
	 */
	uint8_t detectedGear = (uint8_t)0;
	/**
	 * offset 117
	 */
	uint8_t maxTriggerReentrant = (uint8_t)0;
	/**
	 * units: V
	 * offset 118
	 */
	scaled_channel<uint16_t, 12000, 1> rawLowFuelPressure = (uint16_t)0;
	/**
	 * units: V
	 * offset 120
	 */
	scaled_channel<uint16_t, 12000, 1> rawHighFuelPressure = (uint16_t)0;
	/**
	 * @@GAUGE_NAME_FUEL_PRESSURE_LOW@@
	 * units: kpa
	 * offset 122
	 */
	scaled_channel<int16_t, 30, 1> lowFuelPressure = (int16_t)0;
	/**
	 * @@GAUGE_NAME_DESIRED_GEAR@@
	 * units: gear
	 * offset 124
	 */
	int8_t tcuDesiredGear = (int8_t)0;
	/**
	 * @@GAUGE_NAME_FLEX@@
	 * units: %
	 * offset 125
	 */
	scaled_channel<uint8_t, 2, 1> flexPercent = (uint8_t)0;
	/**
	 * @@GAUGE_NAME_WG_POSITION@@
	 * units: %
	 * offset 126
	 */
	scaled_channel<int16_t, 200, 1> wastegatePositionSensor = (int16_t)0;
	/**
	 * @@GAUGE_NAME_FUEL_PRESSURE_HIGH@@
	 * units: bar
	 * offset 128
	 */
	scaled_channel<int16_t, 10, 1> highFuelPressure = (int16_t)0;
	/**
	 * need 4 byte alignment
	 * units: units
	 * offset 130
	 */
	uint8_t alignmentFill_at_130[2] = {};
	/**
	 * offset 132
	 */
	float calibrationValue = (float)0;
	/**
	 * offset 136
	 */
	uint8_t calibrationMode = (uint8_t)0;
	/**
	 * Idle: Stepper target position
	 * offset 137
	 */
	uint8_t idleStepperTargetPosition = (uint8_t)0;
	/**
	 * need 4 byte alignment
	 * units: units
	 * offset 138
	 */
	uint8_t alignmentFill_at_138[2] = {};
	/**
	 * @@GAUGE_NAME_TRG_ERR@@
	 * units: counter
	 * offset 140
	 */
	uint32_t totalTriggerErrorCounter = (uint32_t)0;
	/**
	 * offset 144
	 */
	uint32_t orderingErrorCounter = (uint32_t)0;
	/**
	 * @@GAUGE_NAME_WARNING_COUNTER@@
	 * units: count
	 * offset 148
	 */
	uint16_t warningCounter = (uint16_t)0;
	/**
	 * @@GAUGE_NAME_WARNING_LAST@@
	 * units: error
	 * offset 150
	 */
	uint16_t lastErrorCode = (uint16_t)0;
	/**
	 * Warning code
	 * units: error
	 * offset 152
	 */
	uint16_t recentErrorCode[8] = {};
	/**
	 * EGT
	 * units: deg C
	 * offset 168
	 */
	scaled_channel<int16_t, 4, 1> egt[EGT_CHANNEL_COUNT] = {};
	/**
	 * units: V
	 * offset 184
	 */
	scaled_channel<uint16_t, 12000, 1> rawTps1Primary = (uint16_t)0;
	/**
	 * units: V
	 * offset 186
	 */
	scaled_channel<uint16_t, 12000, 1> rawClt = (uint16_t)0;
	/**
	 * units: V
	 * offset 188
	 */
	scaled_channel<uint16_t, 12000, 1> rawIat = (uint16_t)0;
	/**
	 * units: V
	 * offset 190
	 */
	scaled_channel<uint16_t, 12000, 1> rawOilPressure = (uint16_t)0;
	/**
	 * units: V
	 * offset 192
	 */
	scaled_channel<uint16_t, 12000, 1> rawOilTemperature = (uint16_t)0;
	/**
	 * units: V
	 * offset 194
	 */
	scaled_channel<uint16_t, 12000, 1> rawAcPressure = (uint16_t)0;
	/**
	 * units: V
	 * offset 196
	 */
	scaled_channel<uint16_t, 12000, 1> rawFuelLevel = (uint16_t)0;
	/**
	 * need 4 byte alignment
	 * units: units
	 * offset 198
	 */
	uint8_t alignmentFill_at_198[2] = {};
	/**
	 * units: V
	 * offset 200
	 */
	float rawPpsPrimary = (float)0;
	/**
	 * units: V
	 * offset 204
	 */
	float rawPpsSecondary = (float)0;
	/**
	 * units: V
	 * offset 208
	 */
	float rawRawPpsPrimary = (float)0;
	/**
	 * units: V
	 * offset 212
	 */
	float rawRawPpsSecondary = (float)0;
	/**
	 * @@GAUGE_NAME_IDLE_POSITION@@
	 * units: %
	 * offset 216
	 */
	scaled_channel<int16_t, 200, 1> idlePositionSensor = (int16_t)0;
	/**
	 * @@GAUGE_NAME_AFR@@
	 * units: AFR
	 * offset 218
	 */
	scaled_channel<uint16_t, 1000, 1> AFRValue = (uint16_t)0;
	/**
	 * @@GAUGE_NAME_AFR2@@
	 * units: AFR
	 * offset 220
	 */
	scaled_channel<uint16_t, 1000, 1> AFRValue2 = (uint16_t)0;
	/**
	 * Vss Accel
	 * units: m/s2
	 * offset 222
	 */
	scaled_channel<uint16_t, 300, 1> VssAcceleration = (uint16_t)0;
	/**
	 * @@GAUGE_NAME_LAMBDA2@@
	 * offset 224
	 */
	scaled_channel<uint16_t, 10000, 1> lambdaValue2 = (uint16_t)0;
	/**
	 * @@GAUGE_NAME_VVT_B1E@@
	 * units: deg
	 * offset 226
	 */
	scaled_channel<int16_t, 50, 1> vvtPositionB1E = (int16_t)0;
	/**
	 * @@GAUGE_NAME_VVT_B2I@@
	 * units: deg
	 * offset 228
	 */
	scaled_channel<int16_t, 50, 1> vvtPositionB2I = (int16_t)0;
	/**
	 * @@GAUGE_NAME_VVT_B2E@@
	 * units: deg
	 * offset 230
	 */
	scaled_channel<int16_t, 50, 1> vvtPositionB2E = (int16_t)0;
	/**
	 * Fuel: Trim bank
	 * units: %
	 * offset 232
	 */
	scaled_channel<int16_t, 200, 1> fuelPidCorrection[STFT_BANK_COUNT] = {};
	/**
	 * units: V
	 * offset 236
	 */
	scaled_channel<uint16_t, 12000, 1> rawTps1Secondary = (uint16_t)0;
	/**
	 * units: V
	 * offset 238
	 */
	scaled_channel<uint16_t, 12000, 1> rawTps2Primary = (uint16_t)0;
	/**
	 * units: V
	 * offset 240
	 */
	scaled_channel<uint16_t, 12000, 1> rawTps2Secondary = (uint16_t)0;
	/**
	 * need 4 byte alignment
	 * units: units
	 * offset 242
	 */
	uint8_t alignmentFill_at_242[2] = {};
	/**
	 * @@GAUGE_NAME_ACCEL_VERT@@
	 * units: G
	 * offset 244
	 */
	float accelerationVert = (float)0;
	/**
	 * @@GAUGE_NAME_GYRO_YAW@@
	 * units: deg/sec
	 * offset 248
	 */
	scaled_channel<int16_t, 1000, 1> gyroYaw = (int16_t)0;
	/**
	 * units: deg
	 * offset 250
	 */
	int8_t vvtTargets[4] = {};
	/**
	 * @@GAUGE_NAME_TURBO_SPEED@@
	 * units: hz
	 * offset 254
	 */
	uint16_t turboSpeed = (uint16_t)0;
	/**
	 * Ign: Timing Cyl
	 * units: deg
	 * offset 256
	 */
	scaled_channel<int16_t, 50, 1> ignitionAdvanceCyl[MAX_CYLINDER_COUNT] = {};
	/**
	 * units: %
	 * offset 280
	 */
	scaled_channel<int16_t, 200, 1> tps1Split = (int16_t)0;
	/**
	 * units: %
	 * offset 282
	 */
	scaled_channel<int16_t, 200, 1> tps2Split = (int16_t)0;
	/**
	 * units: %
	 * offset 284
	 */
	scaled_channel<int16_t, 200, 1> tps12Split = (int16_t)0;
	/**
	 * units: %
	 * offset 286
	 */
	scaled_channel<int16_t, 200, 1> accPedalSplit = (int16_t)0;
	/**
	 * Ign: Cut Code
	 * units: code
	 * offset 288
	 */
	int8_t sparkCutReason = (int8_t)0;
	/**
	 * Fuel: Cut Code
	 * units: code
	 * offset 289
	 */
	int8_t fuelCutReason = (int8_t)0;
	/**
	 * @@GAUGE_NAME_AIR_FLOW_ESTIMATE@@
	 * units: kg/h
	 * offset 290
	 */
	scaled_channel<uint16_t, 25, 1> mafEstimate = (uint16_t)0;
	/**
	 * sync: instant RPM
	 * units: rpm
	 * offset 292
	 */
	uint16_t instantRpm = (uint16_t)0;
	/**
	 * units: V
	 * offset 294
	 */
	scaled_channel<uint16_t, 12000, 1> rawMap = (uint16_t)0;
	/**
	 * units: V
	 * offset 296
	 */
	scaled_channel<uint16_t, 12000, 1> rawAfr = (uint16_t)0;
	/**
	 * need 4 byte alignment
	 * units: units
	 * offset 298
	 */
	uint8_t alignmentFill_at_298[2] = {};
	/**
	 * offset 300
	 */
	float calibrationValue2 = (float)0;
	/**
	 * Lua: Tick counter
	 * units: count
	 * offset 304
	 */
	uint32_t luaInvocationCounter = (uint32_t)0;
	/**
	 * Lua: Last tick duration
	 * units: nt
	 * offset 308
	 */
	uint32_t luaLastCycleDuration = (uint32_t)0;
	/**
	 * offset 312
	 */
	uint32_t vssEdgeCounter = (uint32_t)0;
	/**
	 * offset 316
	 */
	uint32_t issEdgeCounter = (uint32_t)0;
	/**
	 * @@GAUGE_NAME_AUX_LINEAR_1@@
	 * offset 320
	 */
	float auxLinear1 = (float)0;
	/**
	 * @@GAUGE_NAME_AUX_LINEAR_2@@
	 * offset 324
	 */
	float auxLinear2 = (float)0;
	/**
	 * @@GAUGE_NAME_AUX_LINEAR_3@@
	 * offset 328
	 */
	float auxLinear3 = (float)0;
	/**
	 * @@GAUGE_NAME_AUX_LINEAR_4@@
	 * offset 332
	 */
	float auxLinear4 = (float)0;
	/**
	 * units: V
	 * offset 336
	 */
	scaled_channel<uint16_t, 12000, 1> rawAuxLinear1 = (uint16_t)0;
	/**
	 * units: V
	 * offset 338
	 */
	scaled_channel<uint16_t, 12000, 1> rawAuxLinear2 = (uint16_t)0;
	/**
	 * units: V
	 * offset 340
	 */
	scaled_channel<uint16_t, 12000, 1> rawAuxLinear3 = (uint16_t)0;
	/**
	 * units: V
	 * offset 342
	 */
	scaled_channel<uint16_t, 12000, 1> rawAuxLinear4 = (uint16_t)0;
	/**
	 * units: kPa
	 * offset 344
	 */
	scaled_channel<uint16_t, 10, 1> fallbackMap = (uint16_t)0;
	/**
	 * Instant MAP
	 * units: kPa
	 * offset 346
	 */
	scaled_channel<uint16_t, 100, 1> instantMAPValue = (uint16_t)0;
	/**
	 * Instant MAF
	 * units: kg/h
	 * offset 348
	 */
	scaled_channel<uint16_t, 25, 1> instantMAFValue = (uint16_t)0;
	/**
	 * units: us
	 * offset 350
	 */
	uint16_t maxLockedDuration = (uint16_t)0;
	/**
	 * @@GAUGE_NAME_CAN_WRITE_OK@@
	 * offset 352
	 */
	uint16_t canWriteOk = (uint16_t)0;
	/**
	 * @@GAUGE_NAME_CAN_WRITE_ERR@@
	 * offset 354
	 */
	uint16_t canWriteNotOk = (uint16_t)0;
	/**
	 * offset 356
	 */
	uint32_t triggerPrimaryFall = (uint32_t)0;
	/**
	 * offset 360
	 */
	uint32_t triggerPrimaryRise = (uint32_t)0;
	/**
	 * offset 364
	 */
	uint32_t triggerSecondaryFall = (uint32_t)0;
	/**
	 * offset 368
	 */
	uint32_t triggerSecondaryRise = (uint32_t)0;
	/**
	 * offset 372
	 */
	uint16_t triggerVvtFall = (uint16_t)0;
	/**
	 * offset 374
	 */
	uint16_t triggerVvtRise = (uint16_t)0;
	/**
	 * offset 376
	 */
	uint16_t triggerVvt2Fall = (uint16_t)0;
	/**
	 * offset 378
	 */
	uint16_t triggerVvt2Rise = (uint16_t)0;
	/**
	 * offset 380
	 */
	uint8_t starterState = (uint8_t)0;
	/**
	 * offset 381
	 */
	uint8_t starterRelayDisable = (uint8_t)0;
	/**
	 * Ign: Multispark count
	 * offset 382
	 */
	uint8_t multiSparkCounter = (uint8_t)0;
	/**
	 * offset 383
	 */
	uint8_t extiOverflowCount = (uint8_t)0;
	/**
	 * offset 384
	 */
	pid_status_s alternatorStatus;
	/**
	 * offset 400
	 */
	pid_status_s idleStatus;
	/**
	 * offset 416
	 */
	pid_status_s etbStatus;
	/**
	 * offset 432
	 */
	pid_status_s boostStatus;
	/**
	 * offset 448
	 */
	pid_status_s wastegateDcStatus;
	/**
	 * offset 464
	 */
	pid_status_s vvtStatus[CAM_INPUTS_COUNT] = {};
	/**
	 * Aux speed 1
	 * units: s
	 * offset 528
	 */
	uint16_t auxSpeed1 = (uint16_t)0;
	/**
	 * Aux speed 2
	 * units: s
	 * offset 530
	 */
	uint16_t auxSpeed2 = (uint16_t)0;
	/**
	 * Aux speed 3
	 * units: s
	 * offset 532
	 */
	uint16_t auxSpeed3 = (uint16_t)0;
	/**
	 * Aux speed 4
	 * units: s
	 * offset 534
	 */
	uint16_t auxSpeed4 = (uint16_t)0;
	/**
	 * @@GAUGE_NAME_ISS@@
	 * units: RPM
	 * offset 536
	 */
	uint16_t ISSValue = (uint16_t)0;
	/**
	 * units: V
	 * offset 538
	 */
	scaled_channel<uint16_t, 12000, 1> rawAnalogInput[LUA_ANALOG_INPUT_COUNT] = {};
	/**
	 * GPPWM Output
	 * units: %
	 * offset 554
	 */
	scaled_channel<uint8_t, 2, 1> gppwmOutput[4] = {};
	/**
	 * offset 558
	 */
	scaled_channel<int16_t, 1, 1> gppwmXAxis[4] = {};
	/**
	 * offset 566
	 */
	scaled_channel<int16_t, 10, 1> gppwmYAxis[4] = {};
	/**
	 * units: V
	 * offset 574
	 */
	scaled_channel<uint16_t, 3000, 1> rawBattery = (uint16_t)0;
	/**
	 * offset 576
	 */
	scaled_channel<int16_t, 10, 1> ignBlendParameter[IGN_BLEND_COUNT] = {};
	/**
	 * units: %
	 * offset 584
	 */
	scaled_channel<uint8_t, 2, 1> ignBlendBias[IGN_BLEND_COUNT] = {};
	/**
	 * units: deg
	 * offset 588
	 */
	scaled_channel<int16_t, 100, 1> ignBlendOutput[IGN_BLEND_COUNT] = {};
	/**
	 * offset 596
	 */
	scaled_channel<int16_t, 10, 1> veBlendParameter[VE_BLEND_COUNT] = {};
	/**
	 * units: %
	 * offset 604
	 */
	scaled_channel<uint8_t, 2, 1> veBlendBias[VE_BLEND_COUNT] = {};
	/**
	 * units: %
	 * offset 608
	 */
	scaled_channel<int16_t, 100, 1> veBlendOutput[VE_BLEND_COUNT] = {};
	/**
	 * offset 616
	 */
	scaled_channel<int16_t, 10, 1> boostOpenLoopBlendParameter[BOOST_BLEND_COUNT] = {};
	/**
	 * units: %
	 * offset 620
	 */
	scaled_channel<uint8_t, 2, 1> boostOpenLoopBlendBias[BOOST_BLEND_COUNT] = {};
	/**
	 * units: %
	 * offset 622
	 */
	scaled_channel<int8_t, 1, 1> boostOpenLoopBlendOutput[BOOST_BLEND_COUNT] = {};
	/**
	 * offset 624
	 */
	scaled_channel<int16_t, 10, 1> boostClosedLoopBlendParameter[BOOST_BLEND_COUNT] = {};
	/**
	 * units: %
	 * offset 628
	 */
	scaled_channel<uint8_t, 2, 1> boostClosedLoopBlendBias[BOOST_BLEND_COUNT] = {};
	/**
	 * units: %
	 * offset 630
	 */
	scaled_channel<int16_t, 10, 1> boostClosedLoopBlendOutput[BOOST_BLEND_COUNT] = {};
	/**
	 * offset 634
	 */
	scaled_channel<int16_t, 10, 1> targetAfrBlendParameter[TARGET_AFR_BLEND_COUNT] = {};
	/**
	 * units: %
	 * offset 638
	 */
	scaled_channel<uint8_t, 2, 1> targetAfrBlendBias[TARGET_AFR_BLEND_COUNT] = {};
	/**
	 * units: %
	 * offset 640
	 */
	scaled_channel<int16_t, 10, 1> targetAfrBlendOutput[TARGET_AFR_BLEND_COUNT] = {};
	/**
	offset 644 bit 0 */
	bool coilState1 : 1 {};
	/**
	offset 644 bit 1 */
	bool coilState2 : 1 {};
	/**
	offset 644 bit 2 */
	bool coilState3 : 1 {};
	/**
	offset 644 bit 3 */
	bool coilState4 : 1 {};
	/**
	offset 644 bit 4 */
	bool coilState5 : 1 {};
	/**
	offset 644 bit 5 */
	bool coilState6 : 1 {};
	/**
	offset 644 bit 6 */
	bool coilState7 : 1 {};
	/**
	offset 644 bit 7 */
	bool coilState8 : 1 {};
	/**
	offset 644 bit 8 */
	bool coilState9 : 1 {};
	/**
	offset 644 bit 9 */
	bool coilState10 : 1 {};
	/**
	offset 644 bit 10 */
	bool coilState11 : 1 {};
	/**
	offset 644 bit 11 */
	bool coilState12 : 1 {};
	/**
	offset 644 bit 12 */
	bool injectorState1 : 1 {};
	/**
	offset 644 bit 13 */
	bool injectorState2 : 1 {};
	/**
	offset 644 bit 14 */
	bool injectorState3 : 1 {};
	/**
	offset 644 bit 15 */
	bool injectorState4 : 1 {};
	/**
	offset 644 bit 16 */
	bool injectorState5 : 1 {};
	/**
	offset 644 bit 17 */
	bool injectorState6 : 1 {};
	/**
	offset 644 bit 18 */
	bool injectorState7 : 1 {};
	/**
	offset 644 bit 19 */
	bool injectorState8 : 1 {};
	/**
	offset 644 bit 20 */
	bool injectorState9 : 1 {};
	/**
	offset 644 bit 21 */
	bool injectorState10 : 1 {};
	/**
	offset 644 bit 22 */
	bool injectorState11 : 1 {};
	/**
	offset 644 bit 23 */
	bool injectorState12 : 1 {};
	/**
	offset 644 bit 24 */
	bool triggerChannel1 : 1 {};
	/**
	offset 644 bit 25 */
	bool triggerChannel2 : 1 {};
	/**
	 * bank 1 intake cam input
	offset 644 bit 26 */
	bool vvtChannel1 : 1 {};
	/**
	 * bank 1 exhaust cam input
	offset 644 bit 27 */
	bool vvtChannel2 : 1 {};
	/**
	 * bank 2 intake cam input
	offset 644 bit 28 */
	bool vvtChannel3 : 1 {};
	/**
	 * bank 2 exhaust cam input
	offset 644 bit 29 */
	bool vvtChannel4 : 1 {};
	/**
	offset 644 bit 30 */
	bool unusedBit_238_30 : 1 {};
	/**
	offset 644 bit 31 */
	bool unusedBit_238_31 : 1 {};
	/**
	 * offset 648
	 */
	uint32_t outputRequestPeriod = (uint32_t)0;
	/**
	 * offset 652
	 */
	float mapFast = (float)0;
	/**
	 * Lua: Gauge
	 * units: value
	 * offset 656
	 */
	float luaGauges[LUA_GAUGE_COUNT] = {};
	/**
	 * units: V
	 * offset 688
	 */
	scaled_channel<uint16_t, 12000, 1> rawMaf2 = (uint16_t)0;
	/**
	 * @@GAUGE_NAME_AIR_FLOW_MEASURED_2@@
	 * units: kg/h
	 * offset 690
	 */
	scaled_channel<uint16_t, 25, 1> mafMeasured2 = (uint16_t)0;
	/**
	 * offset 692
	 */
	uint16_t schedulingUsedCount = (uint16_t)0;
	/**
	 * @@GAUGE_NAME_VVS@@
	 * units: kph
	 * offset 694
	 */
	scaled_channel<uint16_t, 100, 1> vehicleSpeedKph = (uint16_t)0;
	/**
	 * Wheel Speed FL
	 * units: kph
	 * offset 696
	 */
	scaled_channel<uint16_t, 100, 1> vehicleSpeedKph1 = (uint16_t)0;
	/**
	 * Wheel Speed FR
	 * units: kph
	 * offset 698
	 */
	scaled_channel<uint16_t, 100, 1> vehicleSpeedKph2 = (uint16_t)0;
	/**
	 * Wheel Speed RL
	 * units: kph
	 * offset 700
	 */
	scaled_channel<uint16_t, 100, 1> vehicleSpeedKph3 = (uint16_t)0;
	/**
	 * Wheel Speed RR
	 * units: kph
	 * offset 702
	 */
	scaled_channel<uint16_t, 100, 1> vehicleSpeedKph4 = (uint16_t)0;
	/**
	 * Wheel Speed Front AVG
	 * units: kph
	 * offset 704
	 */
	scaled_channel<uint16_t, 100, 1> vehicleSpeedKphFrontAvg = (uint16_t)0;
	/**
	 * Wheel Speed Rear AVG
	 * units: kph
	 * offset 706
	 */
	scaled_channel<uint16_t, 100, 1> vehicleSpeedKphRearAvg = (uint16_t)0;
	/**
	 * LeftRightSpeedRef
	 * units: kph
	 * offset 708
	 */
	scaled_channel<uint16_t, 100, 1> tracSpeedLeftRightREF = (uint16_t)0;
	/**
	 * FrontRearSpeedRef
	 * units: kph
	 * offset 710
	 */
	scaled_channel<uint16_t, 100, 1> tracSpeedFrontRearREF = (uint16_t)0;
	/**
	 * units: %
	 * offset 712
	 */
	scaled_channel<uint16_t, 100, 1> Gego = (uint16_t)0;
	/**
	 * units: count
	 * offset 714
	 */
	uint16_t testBenchIter = (uint16_t)0;
	/**
	 * units: deg C
	 * offset 716
	 */
	scaled_channel<int16_t, 100, 1> oilTemp = (int16_t)0;
	/**
	 * units: deg C
	 * offset 718
	 */
	scaled_channel<int16_t, 100, 1> fuelTemp = (int16_t)0;
	/**
	 * units: deg C
	 * offset 720
	 */
	scaled_channel<int16_t, 100, 1> ambientTemp = (int16_t)0;
	/**
	 * units: deg C
	 * offset 722
	 */
	scaled_channel<int16_t, 100, 1> compressorDischargeTemp = (int16_t)0;
	/**
	 * units: kPa
	 * offset 724
	 */
	scaled_channel<uint16_t, 30, 1> compressorDischargePressure = (uint16_t)0;
	/**
	 * units: kPa
	 * offset 726
	 */
	scaled_channel<uint16_t, 30, 1> throttleInletPressure = (uint16_t)0;
	/**
	 * units: sec
	 * offset 728
	 */
	uint16_t ignitionOnTime = (uint16_t)0;
	/**
	 * units: sec
	 * offset 730
	 */
	uint16_t engineRunTime = (uint16_t)0;
	/**
	 * units: km
	 * offset 732
	 */
	scaled_channel<uint16_t, 10, 1> distanceTraveled = (uint16_t)0;
	/**
	 * @@GAUGE_NAME_AFR_GAS_SCALE@@
	 * units: AFR
	 * offset 734
	 */
	scaled_channel<uint16_t, 1000, 1> afrGasolineScale = (uint16_t)0;
	/**
	 * @@GAUGE_NAME_AFR2_GAS_SCALE@@
	 * units: AFR
	 * offset 736
	 */
	scaled_channel<uint16_t, 1000, 1> afr2GasolineScale = (uint16_t)0;
	/**
	 * need 4 byte alignment
	 * units: units
	 * offset 738
	 */
	uint8_t alignmentFill_at_738[2] = {};
	/**
	 * offset 740
	 */
	float wheelSlipRatio = (float)0;
	/**
	 * offset 744
	 */
	float wheelSlipRatioLeftRightFRONT = (float)0;
	/**
	 * offset 748
	 */
	float wheelSlipRatioLeftRightREAR = (float)0;
	/**
	 * offset 752
	 */
	float wheelSlipRatioLeftRightREF = (float)0;
	/**
	 * offset 756
	 */
	float wheelSlipRatioFrontRear = (float)0;
	/**
	 * canBoxTracTrim
	 * units: %
	 * offset 760
	 */
	int8_t canBoxTracTrim = (int8_t)0;
	/**
	 * need 4 byte alignment
	 * units: units
	 * offset 761
	 */
	uint8_t alignmentFill_at_761[1] = {};
	/**
	 * @@GAUGE_NAME_FUEL_LAST_INJECTION_STAGE_2@@
	 * units: ms
	 * offset 762
	 */
	scaled_channel<uint16_t, 300, 1> actualLastInjectionStage2 = (uint16_t)0;
	/**
	 * actualLastInjSTG2PreSmallPw
	 * units: ms
	 * offset 764
	 */
	scaled_channel<uint16_t, 300, 1> actualLastInjSTG2PreSmallPw = (uint16_t)0;
	/**
	 * @@GAUGE_NAME_FUEL_INJ_DUTY_STAGE_2@@
	 * units: %
	 * offset 766
	 */
	scaled_channel<uint8_t, 2, 1> injectorDutyCycleStage2 = (uint8_t)0;
	/**
	 * offset 767
	 */
	uint8_t rawFlexFreq = (uint8_t)0;
	/**
	 * offset 768
	 */
	uint8_t canReWidebandCmdStatus = (uint8_t)0;
	/**
	 * offset 769
	 */
	uint8_t deviceUid = (uint8_t)0;
	/**
	 * offset 770
	 */
	uint16_t mc33810spiErrorCounter = (uint16_t)0;
	/**
	 * offset 772
	 */
	uint8_t sadDwellRatioCounter = (uint8_t)0;
	/**
	 * offset 773
	 */
	uint8_t injectionPrimingCounter = (uint8_t)0;
	/**
	 * need 4 byte alignment
	 * units: units
	 * offset 774
	 */
	uint8_t alignmentFill_at_774[2] = {};
	/**
	 * @@GAUGE_NAME_AC_PRESSURE@@
	 * units: kPa
	 * offset 776
	 */
	float acPressure = (float)0;
	/**
	 * units: V
	 * offset 780
	 */
	scaled_channel<uint16_t, 12000, 1> rawAuxAnalog1 = (uint16_t)0;
	/**
	 * units: V
	 * offset 782
	 */
	scaled_channel<uint16_t, 12000, 1> rawAuxAnalog2 = (uint16_t)0;
	/**
	 * units: V
	 * offset 784
	 */
	scaled_channel<uint16_t, 12000, 1> rawAuxAnalog3 = (uint16_t)0;
	/**
	 * units: V
	 * offset 786
	 */
	scaled_channel<uint16_t, 12000, 1> rawAuxAnalog4 = (uint16_t)0;
	/**
	 * units: V
	 * offset 788
	 */
	scaled_channel<uint16_t, 12000, 1> rawAuxAnalog5 = (uint16_t)0;
	/**
	 * units: V
	 * offset 790
	 */
	scaled_channel<uint16_t, 12000, 1> rawAuxAnalog6 = (uint16_t)0;
	/**
	 * units: V
	 * offset 792
	 */
	scaled_channel<uint16_t, 12000, 1> rawAuxAnalog7 = (uint16_t)0;
	/**
	 * units: V
	 * offset 794
	 */
	scaled_channel<uint16_t, 12000, 1> rawAuxAnalog8 = (uint16_t)0;
	/**
	 * ECU: Fast ADC errors
	 * offset 796
	 */
	uint8_t fastAdcErrorCount = (uint8_t)0;
	/**
	 * ECU: Slow ADC errors
	 * offset 797
	 */
	uint8_t slowAdcErrorCount = (uint8_t)0;
	/**
	 * units: V
	 * offset 798
	 */
	scaled_channel<uint16_t, 12000, 1> rawAuxTemp1 = (uint16_t)0;
	/**
	 * units: V
	 * offset 800
	 */
	scaled_channel<uint16_t, 12000, 1> rawAuxTemp2 = (uint16_t)0;
	/**
	 * units: V
	 * offset 802
	 */
	scaled_channel<uint16_t, 12000, 1> rawAmbientTemp = (uint16_t)0;
	/**
	 * offset 804
	 */
	uint32_t rtcUnixEpochTime = (uint32_t)0;
	/**
	 * offset 808
	 */
	int8_t sparkCutReasonBlinker = (int8_t)0;
	/**
	 * offset 809
	 */
	int8_t fuelCutReasonBlinker = (int8_t)0;
	/**
	 * offset 810
	 */
	int16_t hp = (int16_t)0;
	/**
	 * offset 812
	 */
	int16_t torque = (int16_t)0;
	/**
	 * need 4 byte alignment
	 * units: units
	 * offset 814
	 */
	uint8_t alignmentFill_at_814[2] = {};
	/**
	 * offset 816
	 */
	float throttlePressureRatio = (float)0;
	/**
	 * offset 820
	 */
	float throttleEffectiveAreaOpening = (float)0;
	/**
	 * offset 824
	 */
	uint32_t mcuSerial = (uint32_t)0;
	/**
	 * offset 828
	 */
	int8_t pedalToTpsIndex = (int8_t)0;
	/**
	 * need 4 byte alignment
	 * units: units
	 * offset 829
	 */
	uint8_t alignmentFill_at_829[3] = {};
	/**
	 * Global target AFR trim
	 * units: %
	 * offset 832
	 */
	float globalAFRTrim = (float)0;
	/**
	 * offset 836
	 */
	uint16_t lastCanButtonSeen = (uint16_t)0;
	/**
	 * offset 838
	 */
	uint16_t lastCanButtonFoundIdx = (uint16_t)0;
	/**
	 * offset 840
	 */
	uint8_t sd_error = (uint8_t)0;
	/**
	 * ECU: Fast ADC overruns
	 * offset 841
	 */
	uint8_t fastAdcOverrunCount = (uint8_t)0;
	/**
	 * ECU: Slow ADC overruns
	 * offset 842
	 */
	uint8_t slowAdcOverrunCount = (uint8_t)0;
	/**
	 * ECU: Fast ADC error type
	 * offset 843
	 */
	uint8_t fastAdcLastError = (uint8_t)0;
	/**
	 * ECU: Fast ADC period
	 * units: ticks
	 * offset 844
	 */
	uint16_t fastAdcPeriod = (uint16_t)0;
	/**
	 * ECU: Fast ADC conversions
	 * units: N
	 * offset 846
	 */
	uint16_t fastAdcConversionCount = (uint16_t)0;
	/**
	 * offset 848
	 */
	uint8_t canReWidebandVersion = (uint8_t)0;
	/**
	 * offset 849
	 */
	uint8_t canReWidebandFwDay = (uint8_t)0;
	/**
	 * offset 850
	 */
	uint8_t canReWidebandFwMon = (uint8_t)0;
	/**
	 * offset 851
	 */
	uint8_t canReWidebandFwYear = (uint8_t)0;
	/**
	 * map per cylinder
	 * units: kPa
	 * offset 852
	 */
	scaled_channel<uint16_t, 325, 1> mapPerCylinder[MAX_CYLINDER_COUNT] = {};
	/**
	 * maf per cylinder
	 * units: kg/h
	 * offset 876
	 */
	scaled_channel<uint16_t, 200, 1> mafPerCylinder[MAX_CYLINDER_COUNT] = {};
	/**
	 * canButtons18
	 * offset 900
	 */
	uint8_t canButtons18 = (uint8_t)0;
	/**
	 * need 4 byte alignment
	 * units: units
	 * offset 901
	 */
	uint8_t alignmentFill_at_901[3] = {};
	/**
	offset 904 bit 0 */
	bool canButtonToggle1 : 1 {};
	/**
	offset 904 bit 1 */
	bool canButtonToggle2 : 1 {};
	/**
	offset 904 bit 2 */
	bool canButtonToggle3 : 1 {};
	/**
	offset 904 bit 3 */
	bool canButtonToggle4 : 1 {};
	/**
	offset 904 bit 4 */
	bool canButtonToggle5 : 1 {};
	/**
	offset 904 bit 5 */
	bool canButtonToggle6 : 1 {};
	/**
	offset 904 bit 6 */
	bool canButtonToggle7 : 1 {};
	/**
	offset 904 bit 7 */
	bool canButtonToggle8 : 1 {};
	/**
	offset 904 bit 8 */
	bool unusedBit_336_8 : 1 {};
	/**
	offset 904 bit 9 */
	bool unusedBit_336_9 : 1 {};
	/**
	offset 904 bit 10 */
	bool unusedBit_336_10 : 1 {};
	/**
	offset 904 bit 11 */
	bool unusedBit_336_11 : 1 {};
	/**
	offset 904 bit 12 */
	bool unusedBit_336_12 : 1 {};
	/**
	offset 904 bit 13 */
	bool unusedBit_336_13 : 1 {};
	/**
	offset 904 bit 14 */
	bool unusedBit_336_14 : 1 {};
	/**
	offset 904 bit 15 */
	bool unusedBit_336_15 : 1 {};
	/**
	offset 904 bit 16 */
	bool unusedBit_336_16 : 1 {};
	/**
	offset 904 bit 17 */
	bool unusedBit_336_17 : 1 {};
	/**
	offset 904 bit 18 */
	bool unusedBit_336_18 : 1 {};
	/**
	offset 904 bit 19 */
	bool unusedBit_336_19 : 1 {};
	/**
	offset 904 bit 20 */
	bool unusedBit_336_20 : 1 {};
	/**
	offset 904 bit 21 */
	bool unusedBit_336_21 : 1 {};
	/**
	offset 904 bit 22 */
	bool unusedBit_336_22 : 1 {};
	/**
	offset 904 bit 23 */
	bool unusedBit_336_23 : 1 {};
	/**
	offset 904 bit 24 */
	bool unusedBit_336_24 : 1 {};
	/**
	offset 904 bit 25 */
	bool unusedBit_336_25 : 1 {};
	/**
	offset 904 bit 26 */
	bool unusedBit_336_26 : 1 {};
	/**
	offset 904 bit 27 */
	bool unusedBit_336_27 : 1 {};
	/**
	offset 904 bit 28 */
	bool unusedBit_336_28 : 1 {};
	/**
	offset 904 bit 29 */
	bool unusedBit_336_29 : 1 {};
	/**
	offset 904 bit 30 */
	bool unusedBit_336_30 : 1 {};
	/**
	offset 904 bit 31 */
	bool unusedBit_336_31 : 1 {};
	/**
	 * offset 908
	 */
	uint8_t progPortOutput[PROGPORTS] = {};
	/**
	 * need 4 byte alignment
	 * units: units
	 * offset 930
	 */
	uint8_t alignmentFill_at_930[2] = {};
	/**
	 * offset 932
	 */
	float rawMCP3208_v_[24] = {};
	/**
	offset 1028 bit 0 */
	bool inj1ok : 1 {};
	/**
	offset 1028 bit 1 */
	bool inj2ok : 1 {};
	/**
	offset 1028 bit 2 */
	bool inj3ok : 1 {};
	/**
	offset 1028 bit 3 */
	bool inj4ok : 1 {};
	/**
	offset 1028 bit 4 */
	bool inj5ok : 1 {};
	/**
	offset 1028 bit 5 */
	bool inj6ok : 1 {};
	/**
	offset 1028 bit 6 */
	bool inj7ok : 1 {};
	/**
	offset 1028 bit 7 */
	bool inj8ok : 1 {};
	/**
	offset 1028 bit 8 */
	bool inj9ok : 1 {};
	/**
	offset 1028 bit 9 */
	bool inj10ok : 1 {};
	/**
	offset 1028 bit 10 */
	bool inj11ok : 1 {};
	/**
	offset 1028 bit 11 */
	bool inj12ok : 1 {};
	/**
	offset 1028 bit 12 */
	bool epic_hall_inp9 : 1 {};
	/**
	offset 1028 bit 13 */
	bool epic_hall_inp10 : 1 {};
	/**
	 * MAF from sensor seems valid
	offset 1028 bit 14 */
	bool isMafValid : 1 {};
	/**
	offset 1028 bit 15 */
	bool unusedbit4 : 1 {};
	/**
	offset 1028 bit 16 */
	bool unusedBit_379_16 : 1 {};
	/**
	offset 1028 bit 17 */
	bool unusedBit_379_17 : 1 {};
	/**
	offset 1028 bit 18 */
	bool unusedBit_379_18 : 1 {};
	/**
	offset 1028 bit 19 */
	bool unusedBit_379_19 : 1 {};
	/**
	offset 1028 bit 20 */
	bool unusedBit_379_20 : 1 {};
	/**
	offset 1028 bit 21 */
	bool unusedBit_379_21 : 1 {};
	/**
	offset 1028 bit 22 */
	bool unusedBit_379_22 : 1 {};
	/**
	offset 1028 bit 23 */
	bool unusedBit_379_23 : 1 {};
	/**
	offset 1028 bit 24 */
	bool unusedBit_379_24 : 1 {};
	/**
	offset 1028 bit 25 */
	bool unusedBit_379_25 : 1 {};
	/**
	offset 1028 bit 26 */
	bool unusedBit_379_26 : 1 {};
	/**
	offset 1028 bit 27 */
	bool unusedBit_379_27 : 1 {};
	/**
	offset 1028 bit 28 */
	bool unusedBit_379_28 : 1 {};
	/**
	offset 1028 bit 29 */
	bool unusedBit_379_29 : 1 {};
	/**
	offset 1028 bit 30 */
	bool unusedBit_379_30 : 1 {};
	/**
	offset 1028 bit 31 */
	bool unusedBit_379_31 : 1 {};
	/**
	 * offset 1032
	 */
	uint8_t epic_dinps18 = (uint8_t)0;
	/**
	 * need 4 byte alignment
	 * units: units
	 * offset 1033
	 */
	uint8_t alignmentFill_at_1033[3] = {};
	/**
	offset 1036 bit 0 */
	bool epic_dinp1 : 1 {};
	/**
	offset 1036 bit 1 */
	bool epic_dinp2 : 1 {};
	/**
	offset 1036 bit 2 */
	bool epic_dinp3 : 1 {};
	/**
	offset 1036 bit 3 */
	bool epic_dinp4 : 1 {};
	/**
	offset 1036 bit 4 */
	bool epic_dinp5 : 1 {};
	/**
	offset 1036 bit 5 */
	bool epic_dinp6 : 1 {};
	/**
	offset 1036 bit 6 */
	bool epic_dinp7 : 1 {};
	/**
	offset 1036 bit 7 */
	bool epic_dinp8 : 1 {};
	/**
	offset 1036 bit 8 */
	bool unusedBit_405_8 : 1 {};
	/**
	offset 1036 bit 9 */
	bool unusedBit_405_9 : 1 {};
	/**
	offset 1036 bit 10 */
	bool unusedBit_405_10 : 1 {};
	/**
	offset 1036 bit 11 */
	bool unusedBit_405_11 : 1 {};
	/**
	offset 1036 bit 12 */
	bool unusedBit_405_12 : 1 {};
	/**
	offset 1036 bit 13 */
	bool unusedBit_405_13 : 1 {};
	/**
	offset 1036 bit 14 */
	bool unusedBit_405_14 : 1 {};
	/**
	offset 1036 bit 15 */
	bool unusedBit_405_15 : 1 {};
	/**
	offset 1036 bit 16 */
	bool unusedBit_405_16 : 1 {};
	/**
	offset 1036 bit 17 */
	bool unusedBit_405_17 : 1 {};
	/**
	offset 1036 bit 18 */
	bool unusedBit_405_18 : 1 {};
	/**
	offset 1036 bit 19 */
	bool unusedBit_405_19 : 1 {};
	/**
	offset 1036 bit 20 */
	bool unusedBit_405_20 : 1 {};
	/**
	offset 1036 bit 21 */
	bool unusedBit_405_21 : 1 {};
	/**
	offset 1036 bit 22 */
	bool unusedBit_405_22 : 1 {};
	/**
	offset 1036 bit 23 */
	bool unusedBit_405_23 : 1 {};
	/**
	offset 1036 bit 24 */
	bool unusedBit_405_24 : 1 {};
	/**
	offset 1036 bit 25 */
	bool unusedBit_405_25 : 1 {};
	/**
	offset 1036 bit 26 */
	bool unusedBit_405_26 : 1 {};
	/**
	offset 1036 bit 27 */
	bool unusedBit_405_27 : 1 {};
	/**
	offset 1036 bit 28 */
	bool unusedBit_405_28 : 1 {};
	/**
	offset 1036 bit 29 */
	bool unusedBit_405_29 : 1 {};
	/**
	offset 1036 bit 30 */
	bool unusedBit_405_30 : 1 {};
	/**
	offset 1036 bit 31 */
	bool unusedBit_405_31 : 1 {};
	/**
	 * offset 1040
	 */
	uint8_t epic_hall_inps18 = (uint8_t)0;
	/**
	 * offset 1041
	 */
	uint8_t epic_hall_inps916 = (uint8_t)0;
	/**
	 * need 4 byte alignment
	 * units: units
	 * offset 1042
	 */
	uint8_t alignmentFill_at_1042[2] = {};
	/**
	offset 1044 bit 0 */
	bool epic_hall_inp1 : 1 {};
	/**
	offset 1044 bit 1 */
	bool epic_hall_inp2 : 1 {};
	/**
	offset 1044 bit 2 */
	bool epic_hall_inp3 : 1 {};
	/**
	offset 1044 bit 3 */
	bool epic_hall_inp4 : 1 {};
	/**
	offset 1044 bit 4 */
	bool epic_hall_inp5 : 1 {};
	/**
	offset 1044 bit 5 */
	bool epic_hall_inp6 : 1 {};
	/**
	offset 1044 bit 6 */
	bool epic_hall_inp7 : 1 {};
	/**
	offset 1044 bit 7 */
	bool epic_hall_inp8 : 1 {};
	/**
	offset 1044 bit 8 */
	bool wheelspeedFLerror : 1 {};
	/**
	offset 1044 bit 9 */
	bool wheelspeedFRerror : 1 {};
	/**
	offset 1044 bit 10 */
	bool wheelspeedRLerror : 1 {};
	/**
	offset 1044 bit 11 */
	bool wheelspeedRRerror : 1 {};
	/**
	offset 1044 bit 12 */
	bool wheelspeedFrontAvgError : 1 {};
	/**
	offset 1044 bit 13 */
	bool wheelspeedRearAvgError : 1 {};
	/**
	offset 1044 bit 14 */
	bool wheelspeedAvgError : 1 {};
	/**
	offset 1044 bit 15 */
	bool tracDisabled : 1 {};
	/**
	offset 1044 bit 16 */
	bool unusedBit_448_16 : 1 {};
	/**
	offset 1044 bit 17 */
	bool unusedBit_448_17 : 1 {};
	/**
	offset 1044 bit 18 */
	bool unusedBit_448_18 : 1 {};
	/**
	offset 1044 bit 19 */
	bool unusedBit_448_19 : 1 {};
	/**
	offset 1044 bit 20 */
	bool unusedBit_448_20 : 1 {};
	/**
	offset 1044 bit 21 */
	bool unusedBit_448_21 : 1 {};
	/**
	offset 1044 bit 22 */
	bool unusedBit_448_22 : 1 {};
	/**
	offset 1044 bit 23 */
	bool unusedBit_448_23 : 1 {};
	/**
	offset 1044 bit 24 */
	bool unusedBit_448_24 : 1 {};
	/**
	offset 1044 bit 25 */
	bool unusedBit_448_25 : 1 {};
	/**
	offset 1044 bit 26 */
	bool unusedBit_448_26 : 1 {};
	/**
	offset 1044 bit 27 */
	bool unusedBit_448_27 : 1 {};
	/**
	offset 1044 bit 28 */
	bool unusedBit_448_28 : 1 {};
	/**
	offset 1044 bit 29 */
	bool unusedBit_448_29 : 1 {};
	/**
	offset 1044 bit 30 */
	bool unusedBit_448_30 : 1 {};
	/**
	offset 1044 bit 31 */
	bool unusedBit_448_31 : 1 {};
	/**
	 * offset 1048
	 */
	scaled_channel<uint8_t, 20, 1> SparkLatencyCorrection = (uint8_t)0;
	/**
	 * offset 1049
	 */
	uint8_t baroHasPressure = (uint8_t)0;
	/**
	 * offset 1050
	 */
	uint8_t baroHasNoPressure = (uint8_t)0;
	/**
	 * need 4 byte alignment
	 * units: units
	 * offset 1051
	 */
	uint8_t alignmentFill_at_1051[1] = {};
	/**
	offset 1052 bit 0 */
	bool stage1InjSmallPwActive : 1 {};
	/**
	offset 1052 bit 1 */
	bool stage2InjSmallPwActive : 1 {};
	/**
	offset 1052 bit 2 */
	bool isMafAveraging : 1 {};
	/**
	offset 1052 bit 3 */
	bool stftNotUpdating : 1 {};
	/**
	offset 1052 bit 4 */
	bool stftNotCorrecting : 1 {};
	/**
	offset 1052 bit 5 */
	bool unusedBit114 : 1 {};
	/**
	offset 1052 bit 6 */
	bool unusedBit115 : 1 {};
	/**
	offset 1052 bit 7 */
	bool unusedBit116 : 1 {};
	/**
	offset 1052 bit 8 */
	bool unusedBit_476_8 : 1 {};
	/**
	offset 1052 bit 9 */
	bool unusedBit_476_9 : 1 {};
	/**
	offset 1052 bit 10 */
	bool unusedBit_476_10 : 1 {};
	/**
	offset 1052 bit 11 */
	bool unusedBit_476_11 : 1 {};
	/**
	offset 1052 bit 12 */
	bool unusedBit_476_12 : 1 {};
	/**
	offset 1052 bit 13 */
	bool unusedBit_476_13 : 1 {};
	/**
	offset 1052 bit 14 */
	bool unusedBit_476_14 : 1 {};
	/**
	offset 1052 bit 15 */
	bool unusedBit_476_15 : 1 {};
	/**
	offset 1052 bit 16 */
	bool unusedBit_476_16 : 1 {};
	/**
	offset 1052 bit 17 */
	bool unusedBit_476_17 : 1 {};
	/**
	offset 1052 bit 18 */
	bool unusedBit_476_18 : 1 {};
	/**
	offset 1052 bit 19 */
	bool unusedBit_476_19 : 1 {};
	/**
	offset 1052 bit 20 */
	bool unusedBit_476_20 : 1 {};
	/**
	offset 1052 bit 21 */
	bool unusedBit_476_21 : 1 {};
	/**
	offset 1052 bit 22 */
	bool unusedBit_476_22 : 1 {};
	/**
	offset 1052 bit 23 */
	bool unusedBit_476_23 : 1 {};
	/**
	offset 1052 bit 24 */
	bool unusedBit_476_24 : 1 {};
	/**
	offset 1052 bit 25 */
	bool unusedBit_476_25 : 1 {};
	/**
	offset 1052 bit 26 */
	bool unusedBit_476_26 : 1 {};
	/**
	offset 1052 bit 27 */
	bool unusedBit_476_27 : 1 {};
	/**
	offset 1052 bit 28 */
	bool unusedBit_476_28 : 1 {};
	/**
	offset 1052 bit 29 */
	bool unusedBit_476_29 : 1 {};
	/**
	offset 1052 bit 30 */
	bool unusedBit_476_30 : 1 {};
	/**
	offset 1052 bit 31 */
	bool unusedBit_476_31 : 1 {};
	/**
	 * offset 1056
	 */
	uint32_t baroCounts = (uint32_t)0;
	/**
	 * units: %
	 * offset 1060
	 */
	scaled_channel<uint16_t, 200, 1> mafmapBlendPercentage = (uint16_t)0;
	/**
	 * units: %
	 * offset 1062
	 */
	scaled_channel<uint16_t, 200, 1> mafmapAirmassSplit = (uint16_t)0;
	/**
	 * offset 1064
	 */
	float runningAirmass = (float)0;
	/**
	 * "afr Error %"
	 * units: %
	 * offset 1068
	 */
	scaled_channel<uint16_t, 200, 1> afrError = (uint16_t)0;
	/**
	 * need 4 byte alignment
	 * units: units
	 * offset 1070
	 */
	uint8_t alignmentFill_at_1070[2] = {};
	/**
	 * offset 1072
	 */
	float tunedMassAirflow = (float)0;
	/**
	 * offset 1076
	 */
	uint8_t unusedAtTheEnd[8] = {};
	/**
	 * offset 1084
	 */
	uint8_t dtTuneCurCycle = (uint8_t)0;
	/**
	 * offset 1085
	 */
	uint8_t dtTuneInjModeOverride = (uint8_t)0;
	/**
	 * need 4 byte alignment
	 * units: units
	 * offset 1086
	 */
	uint8_t alignmentFill_at_1086[2] = {};
};
static_assert(sizeof(output_channels_s) == 1088);

// end
// this section was generated automatically by rusEFI tool config_definition_base-all.jar based on (unknown script) console/binary/output_channels.txt
