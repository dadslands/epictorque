/**
 * @file torque_integration.h
 * @brief Integration header for torque control system
 */

#pragma once

#include "global.h"

// Forward declarations
class TorqueControl;

// Global torque control instance
extern TorqueControl torqueControlModule;

// Initialization functions
void initTorqueSystem();
void initTorqueControlDefaults();
void initTorqueTables();

// Control functions
bool enableTorqueControl();
void disableTorqueControl();
bool isTorqueControlEnabled();

// Console command registration
void registerTorqueCommands();

// Integration with main engine callbacks
void torqueControlFastCallback();
void torqueControlSlowCallback();

// CAN integration
void processTorqueCANMessage(uint32_t canId, const uint8_t* data, uint8_t dlc);

// Safety and diagnostics
bool torqueControlSelfTest();
void torqueControlEmergencyShutdown();
