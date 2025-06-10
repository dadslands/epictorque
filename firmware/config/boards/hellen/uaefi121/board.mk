# Combine the related files for a specific platform and MCU.

# Target ECU board design
BOARDCPPSRC = $(BOARD_DIR)/board_configuration_uaefi121.cpp \
  $(BOARD_DIR)/mega-uaefi.cpp \


#no mux on mm100

# Add them all together
DDEFS += -DFIRMWARE_ID=\"uaefi121\" $(VAR_DEF_ENGINE_TYPE)
# EGT chip
DDEFS += -DEFI_MAX_31855=TRUE


DDEFS += -DSTM32_ICU_USE_TIM1=TRUE -DSTM32_PWM_USE_TIM1=FALSE
DDEFS += -DEFI_SENT_SUPPORT=TRUE




include $(BOARD_DIR)/mega-uaefi.mk

DDEFS += $(PRIMARY_COMMUNICATION_PORT_USART2)

DDEFS += -DUSB_DESCRIPTOR_B_LENGTH=30
DDEFS += -DUSB_DESCRIPTOR_STRING_CONTENT="'r', 0, 'u', 0, 's', 0, 'E', 0, 'F', 0, 'I', 0, ' ', 0, 'u', 0, 'a', 0, 'E', 0, 'F', 0, 'I', 0, '1', 0, '2', 0, '1', 0"


DDEFS += -DRAMDISK_INVALID
