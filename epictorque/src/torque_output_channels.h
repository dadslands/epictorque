/**
 * @file torque_output_channels.h
 * @brief Output channels for torque control system monitoring
 */

#pragma once

#include "global.h"

// Torque control output channels for TunerStudio
struct TorqueOutputChannels {
    // Primary torque values
    float targetTorque;           // Nm - Requested torque
    float actualTorque;           // Nm - Estimated actual torque
    float torqueError;            // Nm - Difference between target and actual
    float pedalTorque;            // Nm - Torque request from pedal
    float tcuTorque;              // Nm - Torque request from TCU
    
    // Actuator outputs
    float targetAirmass;          // g/s - Target airmass for torque
    float actualAirmass;          // g/s - Current airmass
    float targetLoad;             // % - ETB target load
    
    // Control system status
    uint8_t torqueLimiterFlags;   // Bit flags for active limiters
    uint8_t torqueSource;         // 0=pedal, 1=TCU, 2=other
    bool torqueControlActive;     // Torque control enabled and running
    bool fallbackModeActive;      // System in fallback mode
    
    // Sensor health
    bool pedalSensorOk;           // Pedal position sensor healthy
    bool airmassSensorOk;         // Airmass sensor healthy
    bool lambdaSensorOk;          // Lambda sensor healthy
    bool rpmSensorOk;             // RPM sensor healthy
    
    // Communication status
    bool tcuCommOk;               // TCU communication active
    bool canTxOk;                 // CAN transmission working
    uint16_t tcuMessageCount;     // Count of TCU messages received
    uint16_t canErrorCount;       // Count of CAN errors
    
    // Performance metrics
    float controlLoopTime;        // μs - Time for control loop execution
    float modelUpdateTime;        // μs - Time for torque model update
    uint16_t controlFrequency;    // Hz - Actual control loop frequency
    
    // Diagnostic values
    float sparkEfficiency;        // Current spark efficiency factor
    float lambdaEfficiency;       // Current lambda efficiency factor
    float frictionTorque;         // Current friction torque estimate
    float maxAvailableTorque;     // Current maximum torque limit
    
    // Table interpolation debug
    float pedalPosition;          // % - Current pedal position
    float engineRpm;              // RPM - Current engine speed
    float manifoldPressure;       // kPa - Current MAP
    float throttlePosition;       // % - Current throttle position
};

// Bit definitions for torqueLimiterFlags
#define TORQUE_LIMIT_MAX_TORQUE    0x01  // Maximum torque limit active
#define TORQUE_LIMIT_RATE_LIMIT    0x02  // Rate limiter active
#define TORQUE_LIMIT_TCU_OVERRIDE  0x04  // TCU override active
#define TORQUE_LIMIT_SAFETY        0x08  // Safety limiter active
#define TORQUE_LIMIT_THERMAL       0x10  // Thermal protection active
#define TORQUE_LIMIT_FUEL          0x20  // Fuel cut active
#define TORQUE_LIMIT_SPARK         0x40  // Spark cut active
#define TORQUE_LIMIT_USER          0x80  // User-defined limit active

// Torque source definitions
#define TORQUE_SOURCE_PEDAL        0     // Driver pedal request
#define TORQUE_SOURCE_TCU          1     // Transmission control unit
#define TORQUE_SOURCE_CRUISE       2     // Cruise control
#define TORQUE_SOURCE_TRACTION     3     // Traction control
#define TORQUE_SOURCE_STABILITY    4     // Stability control
#define TORQUE_SOURCE_LAUNCH       5     // Launch control
#define TORQUE_SOURCE_ANTILAG      6     // Anti-lag system
#define TORQUE_SOURCE_DIAGNOSTIC   7     // Diagnostic/test mode
