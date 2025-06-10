// file efi_blt_ids.h

// Note that an extended 29-bit CAN identifier is configured by OR-ing with mask 0x80000000.

#ifndef BOOT_COM_CAN_BAUDRATE
/** \brief Configure the desired CAN baudrate. */
#define BOOT_COM_CAN_BAUDRATE           (500000)
#endif

#ifndef BOOT_COM_CAN_RX_MSG_ID
// PC or Android device doing the programming
/** \brief Configure CAN message ID host->target. */
#define BOOT_COM_CAN_RX_MSG_ID          (0x10667 | 0x80000000)
#endif

#ifndef BOOT_COM_CAN_TX_MSG_ID
// ECU talks this CAN is
/** \brief Configure CAN message ID target->host. */
#define BOOT_COM_CAN_TX_MSG_ID          (0x107E1 | 0x80000000)
#endif

#ifndef BOOT_COM_CAN_EXT
#define BOOT_COM_CAN_EXT true
#endif
