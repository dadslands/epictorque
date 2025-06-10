#include "pch.h"
#include "torque_integration.h"

// Engine modules are now managed through the main engine module system
// The torque control module is registered in torque_integration.cpp

void initEngineModules() {
    // Initialize torque control system
    initTorqueSystem();

    // Other engine modules would be initialized here
    efiPrintf("Engine modules initialized");
}
