#pragma once

#define RUSEFI_WIDEBAND_VERSION (0xA0)

// ascii "rus"
#define WB_ACK 0x727573

#define WB_BL_HEADER 0x0EF
#define WB_OPCODE_START 0
#define WB_OPCODE_ERASE 1
#define WB_ERASE_TAG 0x5A5A
#define WB_OPCODE_DATA 2
#define WB_OPCODE_REBOOT 3
#define WB_OPCODE_SET_INDEX 4
#define WB_OPCODE_ECU_STATUS 5
#define WB_OPCODE_PING 6

#define WB_BL_BASE (WB_BL_HEADER << 4)
#define WB_BL_CMD(opcode, extra) (((WB_BL_BASE | (opcode)) << 16) | (extra))

#define WB_BL_CMD_MASK  0X0FFF0000

#define WB_MSG_GET_HEADER(id)   (((id) >> 20) & 0XFFF)
#define WB_MSG_GET_OPCODE(id)   (((id) >> 16) & 0XF)
#define WB_MSG_GET_EXTRA(id)    ((id) & 0XFFFF)

// 0xEF0'0000
#define WB_BL_ENTER WB_BL_CMD(WB_OPCODE_START, 0)
// 0xEF1'5A5A
#define WB_BL_ERASE WB_BL_CMD(WB_OPCODE_ERASE, WB_ERASE_TAG)
// 0xEF2'0000
#define WB_BL_DATA_BASE WB_BL_CMD(WB_OPCODE_DATA, 0)
// 0xEF3'0000
#define WB_BL_REBOOT WB_BL_CMD(WB_OPCODE_REBOOT, 0)
// 0xEF4'0000
#define WB_MSG_SET_INDEX WB_BL_CMD(WB_OPCODE_SET_INDEX, 0)
// 0xEF5'0000
#define WB_MGS_ECU_STATUS WB_BL_CMD(WB_OPCODE_ECU_STATUS, 0)
// 0xEF6'0000
#define WB_MSG_PING WB_BL_CMD(WB_OPCODE_PING, 0)

#define WB_DATA_BASE_ADDR 0x190

// we transmit every 10ms
#define WBO_TX_PERIOD_MS 10

namespace wbo
{
enum class Fault : uint8_t
{
    None = 0,

    // No CAN communication
    CanSilent = 1,
    // Heating is not allowed
    NotAllowed = 2,
    // First fault code at 3 so it's easier to see blink code
    SensorDidntHeat = 3,
    SensorOverheat = 4,
    SensorUnderheat = 5,
    SensorNoHeatSupply = 6,
};

struct StandardData
{
    // DO NOT move the version field - its position and format must be
    // fixed so that incompatible versions can be identified.
    uint8_t Version;
    uint8_t Valid;

    uint16_t Lambda;
    uint16_t TemperatureC;

    uint16_t pad;
};

struct DiagData
{
    uint16_t Esr;
    uint16_t NernstDc;
    uint8_t PumpDuty;
    Fault Status;

    uint8_t HeaterDuty;
    uint8_t pad;
};

struct PongData
{
    uint8_t hwId;
    uint8_t Version;

    // FW build date
    uint8_t year; // starting from 2000
    uint8_t month;
    uint8_t day;

    uint8_t reserved[3];
};

static inline const char* describeFault(Fault fault) {
    switch (fault) {
        case Fault::None:
            return "OK";
        case Fault::CanSilent:
            return "CAN silent";
        case Fault::NotAllowed:
            return "Heating not allowed";
        case Fault::SensorDidntHeat:
            return "Sensor failed to heat";
        case Fault::SensorOverheat:
            return "Sensor overheat";
        case Fault::SensorUnderheat:
            return "Sensor underheat";
        case Fault::SensorNoHeatSupply:
            return "Sensor no heat supply";
    }

    return "Unknown";
}

} // namespace wbo
