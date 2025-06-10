#include "CAN.h"
#include "rusefi.h"

void CANModule::init() {
    // Initialize CAN peripheral with CAN_BUS_SPEED
    canInitialize(CAN_BUS_SPEED);
    canSetRxCallback(canRxCallback); // Assuming callback setup
}

void CANModule::transmit(const CAN_Message& msg) {
    canTransmit(msg.id, msg.data, msg.dlc);
}

// Example RX callback (to be connected in init)
void CANModule::canRxCallback(canid_t id, uint8_t* data, uint8_t dlc) {
    // Process incoming messages here or queue them
}
