#ifndef CAN_H
#define CAN_H

#include "hal.h"  <!-- ChibiOS HAL headers typically use "hal.h" as the main include -->
#include "global.h"
#include "engine.h"

// CAN communication parameters
#define CAN_BUS_SPEED 500U // 500 kbps

// CAN message structure
typedef struct {
    canid_t id;
    uint8_t data[8];
    uint8_t dlc;
} CAN_Message;

// CAN module class
class CANModule : public EngineModule {
public:
    CANModule() {}
    void init() override;
    void transmit(const CAN_Message& msg);
    static void canRxCallback(canid_t id, uint8_t* data, uint8_t dlc);
private:
    // Add any necessary members here
};

#endif // CAN_H
