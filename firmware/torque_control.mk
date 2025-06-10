# Torque Control System Build Configuration
# Add this to your main Makefile or CMakeLists.txt

TORQUE_CONTROL_DIR = $(PROJECT_DIR)/firmware

# Source files for torque control system
TORQUE_CONTROL_SRC = \
	$(TORQUE_CONTROL_DIR)/TorqueControl.cpp \
	$(TORQUE_CONTROL_DIR)/torque_integration.cpp \
	$(TORQUE_CONTROL_DIR)/engine_modules.cpp

# Header files for torque control system  
TORQUE_CONTROL_INC = \
	$(TORQUE_CONTROL_DIR)/TorqueControl.h \
	$(TORQUE_CONTROL_DIR)/torque_integration.h \
	$(TORQUE_CONTROL_DIR)/torque_sensor_types.h \
	$(TORQUE_CONTROL_DIR)/torque_output_channels.h

# Include directories
TORQUE_CONTROL_INCLUDE_DIRS = \
	$(TORQUE_CONTROL_DIR) \
	$(TORQUE_CONTROL_DIR)/config

# Compiler flags for torque control
TORQUE_CONTROL_CFLAGS = \
	-DEFI_TORQUE_CONTROL=1 \
	-DTORQUE_CONTROL_VERSION=1

# Add to main build
FIRMWARE_SOURCES += $(TORQUE_CONTROL_SRC)
FIRMWARE_HEADERS += $(TORQUE_CONTROL_INC)
INCLUDE_DIRS += $(TORQUE_CONTROL_INCLUDE_DIRS)
CFLAGS += $(TORQUE_CONTROL_CFLAGS)
