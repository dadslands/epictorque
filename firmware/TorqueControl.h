j/**
 * @file TorqueControl.h
 * @brief Enhanced Torque-Based Control System for EFI
 * 
 * This module implements comprehensive torque-based engine control with:
 * - Enhanced sensor validation and fault handling
 * - CAN communication with TCU
 * - PID-based actuator control
 * - Torque estimation models
 * - Comprehensive table initialization
 */

#pragma once

#include "global.h"
#include "engine_module.h"
#include "sensor.h"
#include "efi_interpolation.h"
#include "engine_math.h"
#include "error_handling.h"
#include "obd_error_codes.h"
#include "torque_sensor_types.h"
#include "pid.h"

// Enhanced configuration structure with validation and feature flags
typedef struct __attribute__((packed)) {
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

    // Transient prediction parameters
    float manifoldVolume;
    float transientPredictionTime;
} torque_config_s;

// ==================== ENHANCED SENSOR HANDLING ====================
class TorqueSensorManager {
private:
    static constexpr size_t MAX_SENSORS = 32; // Safe upper bound
    efitick_t lastValidReadings[MAX_SENSORS] = {0};  // Track sensor timestamps
    float lastValidValues[MAX_SENSORS] = {0};        // Cache last valid values
    bool errorLogged[MAX_SENSORS] = {false};         // Prevent error spam

public:
    float getValidatedSensor(SensorType type, float fallback, bool useCache = true);
    bool isSensorHealthy(SensorType type);
    void resetSensorError(SensorType type); // Allow error recovery
};

// ==================== ENHANCED TORQUE MODEL ====================
class RusEFITorqueModel {
private:
    float lastEstimatedTorque = 0;
    efitick_t lastUpdateTime = 0;
    
public:
    float estimateEngineTorque(float airmass, float sparkAdvance, float lambda, float rpm);
    
private:
    float getSparkEfficiency(float rpm, float load, float sparkAdvance);
    float getLambdaEfficiency(float lambda);
};

// ==================== ENHANCED ACTUATOR CONTROL ====================
class TorqueActuatorController {
private:
    Pid torquePid;
    float lastTargetAirmass = 0;
    bool usePidControl = false;  // Configuration option

public:
    void init();
    void setTargetTorque(float targetTorque, float currentTorque, float rpm);
    void enablePidControl(bool enable) { usePidControl = enable; }

private:
    float torqueToAirmass(float torque, float rpm);
    void setTargetAirmass(float target);
    float applyAirmassRateLimit(float newAirmass);
};

// ==================== ENHANCED CAN COMMUNICATION ====================
class TorqueCANManager {
private:
    efitick_t lastTCUMessage = 0;
    uint8_t canMessageCounter = 0;
    
public:
    void processTCURequest(const CANRxFrame& frame);
    void sendTorqueStatus();
    bool isTCURequestValid();
    uint16_t getMessageCount() const { return messageCounter; }

private:
    uint8_t buildStatusFlags();
    uint16_t messageCounter = 0;
};

// ==================== ENHANCED MAIN TORQUE CONTROL MODULE ====================
class TorqueControl : public EngineModule {
private:
    TorqueSensorManager sensorManager;
    RusEFITorqueModel torqueModel;
    TorqueActuatorController actuatorController;
    TorqueCANManager canManager;
    
    efitick_t lastControlUpdate = 0;
    float rampedTorqueTarget = 0;
    
public:
    void onSlowCallback() override;
    void onFastCallback() override;
    void init() override;
    
    float getActualTorque();
    
    // TCU communication state
    float tcuTorqueRequest = 0;
    uint8_t tcuPriority = 0;
    uint8_t tcuFlags = 0;
    bool tcuRequestActive = false;
    bool fallbackModeActive = false;
    bool limiterActive = false;
    uint8_t limiterFlags = 0;
    
private:
    float calculatePedalTorque(float pedalPosition);
    float arbitrateRequests(float pedalTorque, float rpm);
    void updateOutputChannels(float target, float actual);
    void updateDiagnostics();
    void updatePerformanceMetrics();
    void initializeTables();

    // Enhanced status methods
    bool isEnabled() const;
    bool isLimiterActive() const;
    bool isFallbackMode() const;
};

// Table initialization function
void initTorqueTables();

// Engine module initialization
void initEngineModules();
void initTorqueControlDefaults();

// Global torque control instance
extern TorqueControl torqueControlModule;
