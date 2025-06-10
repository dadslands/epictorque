#pragma once
#include "../global.h"
#include "../torque_sensor_types.h"
#include "../torque_output_channels.h"

// Enhanced configuration structure with validation and feature flags
struct torque_config_s {
    bool_t torqueControlEnabled;
    float torqueRampRate;               // Nm/s
    bool_t fallbackModeEnabled;
    float maxTorqueLimit;               // Nm
    float minTorqueLimit;               // Nm

    // Feature flags for optional functionality
    bool_t enableAdvancedPid;
    bool_t enableTransientPrediction;
    bool_t enableSparkEfficiencyTables;
    bool_t enableTcuIntegration;

    // Timeout configurations
    uint16_t tcuTimeoutMs;
    uint16_t sensorTimeoutMs;

    // Table definitions
    float pedalToTorqueTable[PEDAL_TO_TORQUE_SIZE];
    float pedalPositionBins[PEDAL_TO_TORQUE_SIZE];

    float torquePerAirmassTable[TORQUE_CURVE_SIZE];
    float torqueRpmBins[TORQUE_CURVE_SIZE];

    float sparkEfficiencyTable[IGN_RPM_COUNT][IGN_LOAD_COUNT];
    float frictionTorqueTable[TORQUE_CURVE_SIZE];
    float maxTorqueTable[TORQUE_CURVE_SIZE];

    // PID parameters for torque control
    pid_s torquePid;

    // Calibration parameters
    float manifoldVolume;
    float transientPredictionTime;
};

// Add torque config to main engine configuration
// This would normally be generated, but for now we add it manually
struct engine_configuration_s {
    // ... existing fields would be here ...
    torque_config_s torqueConfig;
    // ... more existing fields would be here ...
};

// Main output channels structure that includes torque data
// This would normally be part of the main TunerStudioOutputChannels
struct TunerStudioOutputChannels {
    // ... existing output channels would be here ...

    // Torque control outputs
    TorqueOutputChannels torque;

    // Legacy individual fields for backward compatibility
    float targetTorque;
    float actualTorque;
    float torqueError;
    float targetAirmass;
    uint8_t torqueLimiterFlags;
    bool pedalSensorOk;
    bool airmassSensorOk;
    bool torqueControlActive;
    bool tcuCommOk;

    // ... more existing fields would be here ...
};
