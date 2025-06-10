# EpicTorque Installation Guide

## Prerequisites

Before installing EpicTorque, ensure you have:

- **rusEFI firmware development environment** set up
- **Git** for version control
- **Make** or **CMake** for building
- **TunerStudio** for configuration (optional but recommended)
- **CAN hardware** for TCU integration (optional)

## Quick Installation

### Method 1: Direct Integration (Recommended)

1. **Clone EpicTorque into your rusEFI project:**
   ```bash
   cd /path/to/your/rusefi
   git submodule add https://github.com/dadslands/epictorque.git firmware/epictorque
   ```

2. **Copy source files:**
   ```bash
   cp firmware/epictorque/src/* firmware/
   ```

3. **Add to build system:**
   ```bash
   echo "include firmware/epictorque/Makefile" >> Makefile
   ```

4. **Build and flash:**
   ```bash
   make -j8
   make flash
   ```

### Method 2: Standalone Installation

1. **Clone the repository:**
   ```bash
   git clone https://github.com/dadslands/epictorque.git
   cd epictorque
   ```

2. **Install to rusEFI:**
   ```bash
   make install RUSEFI_DIR=/path/to/your/rusefi
   ```

3. **Build rusEFI with EpicTorque:**
   ```bash
   cd /path/to/your/rusefi
   make -j8
   ```

## Detailed Installation Steps

### Step 1: Environment Setup

Ensure your development environment is ready:

```bash
# Ubuntu/Debian
sudo apt-get update
sudo apt-get install build-essential git cmake

# Install rusEFI dependencies
sudo apt-get install gcc-arm-none-eabi openocd

# Optional: Install testing framework
sudo apt-get install libgtest-dev
```

### Step 2: Source Integration

Add EpicTorque source files to your rusEFI firmware:

```bash
# Navigate to your rusEFI firmware directory
cd /path/to/rusefi/firmware

# Copy EpicTorque source files
cp /path/to/epictorque/src/TorqueControl.h .
cp /path/to/epictorque/src/TorqueControl.cpp .
cp /path/to/epictorque/src/torque_integration.h .
cp /path/to/epictorque/src/torque_integration.cpp .
cp /path/to/epictorque/src/torque_sensor_types.h .
cp /path/to/epictorque/src/torque_output_channels.h .
```

### Step 3: Build System Integration

#### For Makefile-based builds:

Add to your main `Makefile`:
```makefile
# EpicTorque source files
FIRMWARE_SOURCES += \
    TorqueControl.cpp \
    torque_integration.cpp

# EpicTorque compiler flags
CFLAGS += -DEFI_TORQUE_CONTROL=1
```

#### For CMake-based builds:

Add to your `CMakeLists.txt`:
```cmake
# EpicTorque source files
set(EPICTORQUE_SOURCES
    TorqueControl.cpp
    torque_integration.cpp
)

# Add to firmware sources
target_sources(firmware PRIVATE ${EPICTORQUE_SOURCES})

# EpicTorque compile definitions
target_compile_definitions(firmware PRIVATE EFI_TORQUE_CONTROL=1)
```

### Step 4: Engine Integration

Add EpicTorque initialization to your main engine initialization:

```cpp
// In engine_controller.cpp or similar
#include "torque_integration.h"

void initEngineController() {
    // ... existing initialization ...
    
    // Initialize EpicTorque system
    initTorqueSystem();
    
    // ... more initialization ...
}
```

Add callbacks to your main engine loops:

```cpp
// In engine.cpp periodicFastCallback()
void Engine::periodicFastCallback() {
    // ... existing fast tasks ...
    
    // EpicTorque fast control loop (100Hz)
    torqueControlFastCallback();
    
    // ... more fast tasks ...
}

// In engine.cpp periodicSlowCallback()
void Engine::periodicSlowCallback() {
    // ... existing slow tasks ...
    
    // EpicTorque slow tasks (10Hz)
    torqueControlSlowCallback();
    
    // ... more slow tasks ...
}
```

### Step 5: Configuration Structure Integration

Add the torque configuration to your main engine configuration structure:

```cpp
// In engine_configuration_generated_structures.h
struct engine_configuration_s {
    // ... existing configuration fields ...
    
    torque_config_s torqueConfig;
    
    // ... more configuration fields ...
};
```

Add output channels to your TunerStudio output structure:

```cpp
// In your main output channels structure
struct TunerStudioOutputChannels {
    // ... existing output channels ...
    
    TorqueOutputChannels torque;
    
    // Legacy individual fields for backward compatibility
    float targetTorque;
    float actualTorque;
    float torqueError;
    
    // ... more output channels ...
};
```

### Step 6: CAN Integration (Optional)

If you want TCU integration, add CAN message handling:

```cpp
// In your CAN receive handler
void canRxCallback(canid_t id, uint8_t* data, uint8_t dlc) {
    // ... existing CAN handlers ...
    
    // Process EpicTorque CAN messages
    processTorqueCANMessage(id, data, dlc);
    
    // ... more CAN handlers ...
}
```

### Step 7: TunerStudio Configuration

Copy the TunerStudio configuration:

```bash
cp /path/to/epictorque/tunerstudio/torque_control.ini /path/to/rusefi/tunerstudio/
```

Add to your main TunerStudio INI file:
```ini
#include "torque_control.ini"
```

## Verification

### Build Verification

1. **Compile the firmware:**
   ```bash
   make clean
   make -j8
   ```

2. **Check for EpicTorque symbols:**
   ```bash
   nm firmware.elf | grep -i torque
   ```

3. **Verify size impact:**
   ```bash
   size firmware.elf
   ```

### Runtime Verification

1. **Flash the firmware:**
   ```bash
   make flash
   ```

2. **Connect to console and test:**
   ```
   > torque_status
   > torque_enable
   > torque_test 100.0
   ```

3. **Check TunerStudio integration:**
   - Open TunerStudio
   - Navigate to EpicTorque configuration pages
   - Verify real-time data display

### Unit Testing

Run the test suite to verify functionality:

```bash
# Build and run tests
make test

# Run performance benchmarks
make benchmark
```

## Troubleshooting

### Common Build Issues

1. **Missing headers:**
   ```
   Error: 'torque_sensor_types.h' not found
   ```
   **Solution:** Ensure all header files are copied to the firmware directory.

2. **Undefined symbols:**
   ```
   Error: undefined reference to 'initTorqueSystem'
   ```
   **Solution:** Ensure `torque_integration.cpp` is added to your build system.

3. **Compilation errors:**
   ```
   Error: 'SensorType' has not been declared
   ```
   **Solution:** Ensure proper include order and rusEFI compatibility.

### Runtime Issues

1. **System won't initialize:**
   - Check console output for error messages
   - Verify sensor availability
   - Run `torque_status` command

2. **No torque control response:**
   - Verify `torqueControlEnabled` is true
   - Check sensor readings with `torque_status`
   - Monitor limiter flags for active restrictions

3. **TunerStudio connection issues:**
   - Verify INI file integration
   - Check output channel definitions
   - Ensure proper page sizes and offsets

## Performance Optimization

### Memory Usage

Monitor memory usage impact:
```bash
# Check RAM usage
size firmware.elf

# Check stack usage during runtime
# Use stack painting or runtime analysis tools
```

### CPU Usage

Profile CPU usage:
```bash
# Enable performance profiling
make CFLAGS+="-DPERF_TRACE=1"

# Monitor control loop timing in TunerStudio
# Target: < 100μs per control cycle
```

## Next Steps

After successful installation:

1. **Read the [Configuration Guide](CONFIGURATION.md)**
2. **Set up [TunerStudio](TUNERSTUDIO.md)**
3. **Configure [CAN Integration](CAN_INTEGRATION.md)** (if needed)
4. **Review [Troubleshooting Guide](TROUBLESHOOTING.md)**

## Support

If you encounter issues:

1. **Check the logs:** Enable debug output and review console messages
2. **Run diagnostics:** Use `torque_status` and built-in self-tests
3. **Community support:** Post on [rusEFI forums](https://rusefi.com/forum/)
4. **GitHub issues:** Report bugs at [EpicTorque Issues](https://github.com/dadslands/epictorque/issues)
