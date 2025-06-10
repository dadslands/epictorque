/**
 * @file torque_sensor_types.h
 * @brief Sensor type definitions for torque control system
 */

#pragma once

// Extend existing SensorType enum for torque control
// These would normally be added to the main sensor.h file
enum class TorqueSensorType {
    AcceleratorPedal = 100,  // Start at high number to avoid conflicts
    AirMass = 101,
    Lambda1 = 102,
    TorqueRequest = 103,
    ActualTorque = 104
};

// Error codes for torque control system
// These would normally be added to obd_error_codes.h
enum class TorqueObdCode : uint16_t {
    OBD_Torque_Sensor_Fault = 0x2000,
    OBD_Torque_CAN_Checksum = 0x2001,
    OBD_Torque_CAN_Invalid = 0x2002,
    OBD_Torque_CAN_Timeout = 0x2003,
    OBD_Torque_Actuator_Fault = 0x2004,
    OBD_Torque_Model_Error = 0x2005,
    OBD_Torque_Limit_Exceeded = 0x2006
};

// CAN message IDs for torque control
#define TCU_TORQUE_REQUEST_ID    0x18F00300  // J1939 PGN 0xF003
#define ECU_TORQUE_STATUS_ID     0x18CFE600  // J1939 PGN 0xCFE6
#define TORQUE_BROADCAST_ID      0x18FEF100  // J1939 PGN 0xFEF1

// Table size constants
#ifndef PEDAL_TO_TORQUE_SIZE
#define PEDAL_TO_TORQUE_SIZE 20
#endif

#ifndef TORQUE_CURVE_SIZE  
#define TORQUE_CURVE_SIZE 100
#endif

#ifndef IGN_RPM_COUNT
#define IGN_RPM_COUNT 16
#endif

#ifndef IGN_LOAD_COUNT
#define IGN_LOAD_COUNT 8
#endif
