/**
 * @file torque_integration.cpp
 * @brief Integration of torque control with main engine system
 */

#include "pch.h"
#include "TorqueControl.h"
#include "torque_integration.h"

// Global torque control instance
TorqueControl torqueControlModule;

/**
 * Initialize torque control system with default values
 */
void initTorqueControlDefaults() {
    auto& config = engineConfiguration->torqueConfig;
    
    // Basic settings
    config.torqueControlEnabled = false;  // Start disabled for safety
    config.fallbackModeEnabled = true;
    config.torqueRampRate = 500.0f;      // Nm/s - reasonable default
    config.maxTorqueLimit = 300.0f;      // Nm - conservative limit
    config.minTorqueLimit = -50.0f;      // Nm - allow some engine braking
    
    // Feature flags - start with basic functionality
    config.enableAdvancedPid = false;
    config.enableTransientPrediction = false;
    config.enableSparkEfficiencyTables = false;
    config.enableTcuIntegration = false;
    
    // Timeouts
    config.tcuTimeoutMs = 200;           // 200ms TCU timeout
    config.sensorTimeoutMs = 100;        // 100ms sensor timeout
    
    // Transient parameters
    config.manifoldVolume = 2.0f;        // Liters - typical intake volume
    config.transientPredictionTime = 50.0f; // ms
    
    // Initialize PID parameters
    config.torquePid.pFactor = 0.5f;
    config.torquePid.iFactor = 0.1f;
    config.torquePid.dFactor = 0.05f;
    config.torquePid.offset = 0;
    config.torquePid.minValue = -50;
    config.torquePid.maxValue = 50;
    
    // Initialize tables
    initTorqueTables();
}

/**
 * Initialize torque control tables with reasonable defaults
 */
void initTorqueTables() {
    auto& config = engineConfiguration->torqueConfig;
    
    // Check if tables are already initialized
    if (config.torqueRpmBins[0] > 0) {
        return; // Already initialized
    }
    
    // RPM bins (500-7000 RPM)
    for (int i = 0; i < TORQUE_CURVE_SIZE; i++) {
        float rpm = 500 + i * (6500.0f / (TORQUE_CURVE_SIZE - 1));
        config.torqueRpmBins[i] = rpm;
        
        // Typical naturally aspirated gasoline engine characteristics
        config.torquePerAirmassTable[i] = 12.0f + sinf(rpm / 1000.0f) * 2.0f;
        config.frictionTorqueTable[i] = 15.0f + rpm * 0.002f;
        
        // Peak torque around 4000 RPM
        float torqueFactor = 1.0f - powf((rpm - 4000.0f) / 3000.0f, 2) * 0.3f;
        config.maxTorqueTable[i] = 250.0f * torqueFactor;
    }
    
    // Pedal position bins (0-100%)
    for (int i = 0; i < PEDAL_TO_TORQUE_SIZE; i++) {
        float pos = i * (100.0f / (PEDAL_TO_TORQUE_SIZE - 1));
        config.pedalPositionBins[i] = pos;
        
        // Progressive pedal mapping (squared curve for better low-speed control)
        config.pedalToTorqueTable[i] = powf(pos / 100.0f, 1.2f) * 200.0f;
    }
    
    // Initialize spark efficiency table if enabled
    if (config.enableSparkEfficiencyTables) {
        for (int rpm = 0; rpm < IGN_RPM_COUNT; rpm++) {
            for (int load = 0; load < IGN_LOAD_COUNT; load++) {
                // Default to 100% efficiency, can be tuned later
                config.sparkEfficiencyTable[rpm][load] = 1.0f;
            }
        }
    }
}

/**
 * Enable torque control with safety checks
 */
bool enableTorqueControl() {
    // Perform safety checks before enabling
    if (!Sensor::hasSensor(SensorType::AcceleratorPedal)) {
        firmwareError(ObdCode::OBD_Torque_Sensor_Fault, "No pedal sensor for torque control");
        return false;
    }
    
    if (!Sensor::hasSensor(SensorType::Rpm)) {
        firmwareError(ObdCode::OBD_Torque_Sensor_Fault, "No RPM sensor for torque control");
        return false;
    }
    
    // Initialize if not already done
    if (!engineConfiguration->torqueConfig.torqueControlEnabled) {
        initTorqueControlDefaults();
    }
    
    // Enable the system
    engineConfiguration->torqueConfig.torqueControlEnabled = true;
    
    efiPrintf("Torque control enabled");
    return true;
}

/**
 * Disable torque control safely
 */
void disableTorqueControl() {
    engineConfiguration->torqueConfig.torqueControlEnabled = false;
    efiPrintf("Torque control disabled");
}

/**
 * Get current torque control status
 */
bool isTorqueControlEnabled() {
    return engineConfiguration->torqueConfig.torqueControlEnabled;
}

/**
 * Console commands for torque control
 */
#if EFI_TUNER_STUDIO
static void cmdEnableTorqueControl() {
    if (enableTorqueControl()) {
        efiPrintf("Torque control enabled successfully");
    } else {
        efiPrintf("Failed to enable torque control - check sensors");
    }
}

static void cmdDisableTorqueControl() {
    disableTorqueControl();
    efiPrintf("Torque control disabled");
}

static void cmdTorqueStatus() {
    auto& config = engineConfiguration->torqueConfig;
    auto& outputs = engine->outputChannels.torque;
    
    efiPrintf("=== Torque Control Status ===");
    efiPrintf("Enabled: %s", config.torqueControlEnabled ? "YES" : "NO");
    efiPrintf("Target Torque: %.1f Nm", outputs.targetTorque);
    efiPrintf("Actual Torque: %.1f Nm", outputs.actualTorque);
    efiPrintf("Pedal Position: %.1f%%", outputs.pedalPosition);
    efiPrintf("Limiter Flags: 0x%02X", outputs.torqueLimiterFlags);
    efiPrintf("Sensor Health: Pedal=%s RPM=%s", 
              outputs.pedalSensorOk ? "OK" : "FAIL",
              outputs.rpmSensorOk ? "OK" : "FAIL");
}

static void cmdTorqueTest(float targetTorque) {
    if (!isTorqueControlEnabled()) {
        efiPrintf("Torque control not enabled");
        return;
    }
    
    if (targetTorque < -50 || targetTorque > 300) {
        efiPrintf("Torque value out of range (-50 to 300 Nm)");
        return;
    }
    
    // This would set a test torque request
    efiPrintf("Test torque request: %.1f Nm", targetTorque);
    // Implementation would depend on test mode setup
}
#endif

/**
 * Register console commands for torque control
 */
void registerTorqueCommands() {
#if EFI_TUNER_STUDIO
    addConsoleAction("torque_enable", cmdEnableTorqueControl);
    addConsoleAction("torque_disable", cmdDisableTorqueControl);
    addConsoleAction("torque_status", cmdTorqueStatus);
    addConsoleActionF("torque_test", cmdTorqueTest);
#endif
}

/**
 * Fast callback for torque control (called from main engine fast callback)
 */
void torqueControlFastCallback() {
    if (isTorqueControlEnabled()) {
        torqueControlModule.onFastCallback();
    }
}

/**
 * Slow callback for torque control (called from main engine slow callback)
 */
void torqueControlSlowCallback() {
    if (isTorqueControlEnabled()) {
        torqueControlModule.onSlowCallback();
    }
}

/**
 * Process CAN messages for torque control
 */
void processTorqueCANMessage(uint32_t canId, const uint8_t* data, uint8_t dlc) {
    if (!isTorqueControlEnabled() || !engineConfiguration->torqueConfig.enableTcuIntegration) {
        return;
    }

    // Check for TCU torque request message
    if (canId == TCU_TORQUE_REQUEST_ID) {
        CANRxFrame frame;
        frame.DLC = dlc;
        if (dlc <= 8) {
            memcpy(frame.data8, data, dlc);
            torqueControlModule.getCanManager().processTCURequest(frame);
        }
    }
}

/**
 * Perform torque control self-test
 */
bool torqueControlSelfTest() {
    efiPrintf("=== Torque Control Self Test ===");

    // Check required sensors
    if (!Sensor::hasSensor(SensorType::AcceleratorPedal)) {
        efiPrintf("FAIL: No accelerator pedal sensor");
        return false;
    }

    if (!Sensor::hasSensor(SensorType::Rpm)) {
        efiPrintf("FAIL: No RPM sensor");
        return false;
    }

    // Check sensor readings
    auto pedalResult = Sensor::get(SensorType::AcceleratorPedal);
    if (!pedalResult.Valid) {
        efiPrintf("FAIL: Pedal sensor not reading");
        return false;
    }

    auto rpmResult = Sensor::get(SensorType::Rpm);
    if (!rpmResult.Valid) {
        efiPrintf("FAIL: RPM sensor not reading");
        return false;
    }

    // Check configuration
    auto& config = engineConfiguration->torqueConfig;
    if (config.maxTorqueLimit <= 0 || config.maxTorqueLimit > 1000) {
        efiPrintf("FAIL: Invalid max torque limit: %.1f", config.maxTorqueLimit);
        return false;
    }

    if (config.torqueRampRate <= 0 || config.torqueRampRate > 10000) {
        efiPrintf("FAIL: Invalid ramp rate: %.1f", config.torqueRampRate);
        return false;
    }

    efiPrintf("PASS: All torque control checks passed");
    return true;
}

/**
 * Emergency shutdown of torque control
 */
void torqueControlEmergencyShutdown() {
    efiPrintf("EMERGENCY: Torque control shutdown");

    // Disable torque control immediately
    engineConfiguration->torqueConfig.torqueControlEnabled = false;

    // Reset all outputs to safe values
    engine->outputChannels.torque.targetTorque = 0;
    engine->outputChannels.torque.targetAirmass = 0;

    // Log the emergency shutdown
    firmwareError(ObdCode::OBD_Torque_Sensor_Fault, "Torque control emergency shutdown");
}

/**
 * Initialize torque control system
 */
void initTorqueSystem() {
    // Initialize defaults
    initTorqueControlDefaults();

    // Initialize the module
    torqueControlModule.init();

    // Register console commands
    registerTorqueCommands();

    // Perform self-test if enabled
    if (engineConfiguration->torqueConfig.torqueControlEnabled) {
        if (!torqueControlSelfTest()) {
            efiPrintf("Torque control self-test failed - disabling");
            disableTorqueControl();
        }
    }

    efiPrintf("Torque control system initialized");
}
