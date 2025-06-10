# Torque-Based Control System

## Overview

This implementation provides a comprehensive torque-based engine control system for rusEFI with enhanced safety features, robust sensor validation, and professional-grade CAN communication.

## Features

### Core Functionality
- **Torque-based throttle control** - Direct torque request to actuator mapping
- **Enhanced sensor validation** - Fault-tolerant sensor reading with caching
- **Rate limiting** - Smooth torque transitions for drivability
- **Safety limits** - Multiple layers of torque limiting for engine protection
- **Diagnostic monitoring** - Comprehensive system health monitoring

### Advanced Features (Configurable)
- **PID control** - Closed-loop torque tracking for precision applications
- **TCU integration** - J1939 CAN communication with transmission control units
- **Transient prediction** - Manifold filling compensation
- **Spark efficiency tables** - Advanced torque modeling

## Architecture

### Main Components

1. **TorqueSensorManager** - Validates and caches sensor readings
2. **RusEFITorqueModel** - Estimates actual engine torque output
3. **TorqueActuatorController** - Controls throttle/airmass to achieve target torque
4. **TorqueCANManager** - Handles CAN communication with external systems
5. **TorqueControl** - Main control module coordinating all components

### File Structure
```
firmware/
├── TorqueControl.h              # Main header with class definitions
├── TorqueControl.cpp            # Core implementation
├── torque_integration.h         # Integration header
├── torque_integration.cpp       # Engine integration and console commands
├── torque_sensor_types.h        # Sensor types and constants
├── torque_output_channels.h     # Output channel definitions
├── test_torque_control.cpp      # Unit tests
├── torque_control.mk           # Build system integration
└── TORQUE_CONTROL_README.md    # This documentation
```

## Configuration

### Basic Setup

1. **Enable torque control**:
   ```cpp
   engineConfiguration->torqueConfig.torqueControlEnabled = true;
   ```

2. **Set torque limits**:
   ```cpp
   engineConfiguration->torqueConfig.maxTorqueLimit = 300.0f;  // Nm
   engineConfiguration->torqueConfig.minTorqueLimit = -50.0f;  // Nm
   ```

3. **Configure ramp rate**:
   ```cpp
   engineConfiguration->torqueConfig.torqueRampRate = 500.0f;  // Nm/s
   ```

### Feature Flags

Enable optional features as needed:
```cpp
// Advanced PID control
engineConfiguration->torqueConfig.enableAdvancedPid = true;

// TCU CAN integration
engineConfiguration->torqueConfig.enableTcuIntegration = true;

// Spark efficiency tables
engineConfiguration->torqueConfig.enableSparkEfficiencyTables = true;

// Transient prediction
engineConfiguration->torqueConfig.enableTransientPrediction = true;
```

### Table Configuration

The system uses several calibration tables:

- **Pedal to Torque Map** - Maps pedal position (0-100%) to torque request (Nm)
- **Torque per Airmass** - Engine torque output per unit airmass at different RPM
- **Friction Torque** - Mechanical losses vs RPM
- **Maximum Torque** - RPM-based torque limits for engine protection

## Console Commands

Use these commands for testing and diagnostics:

- `torque_enable` - Enable torque control system
- `torque_disable` - Disable torque control system  
- `torque_status` - Display current system status
- `torque_test <value>` - Set test torque request (Nm)

## TunerStudio Integration

### Output Channels

Monitor these values in TunerStudio:

- `targetTorque` - Requested torque (Nm)
- `actualTorque` - Estimated actual torque (Nm)
- `torqueError` - Difference between target and actual (Nm)
- `targetAirmass` - Target airmass for torque (g/s)
- `torqueLimiterFlags` - Active limiter status (bitfield)
- `pedalSensorOk` - Pedal sensor health
- `tcuCommOk` - TCU communication status

### Configuration Tables

Tune these tables in TunerStudio:

1. **Pedal to Torque Map**
   - X-axis: Pedal position (%)
   - Y-axis: Torque request (Nm)
   - Use progressive mapping for better low-speed control

2. **Torque per Airmass**
   - X-axis: Engine RPM
   - Y-axis: Torque per unit airmass (Nm/(g/s))
   - Represents engine volumetric efficiency

3. **Maximum Torque Limits**
   - X-axis: Engine RPM  
   - Y-axis: Maximum allowed torque (Nm)
   - Set conservatively for engine protection

## CAN Integration

### TCU Communication

The system supports J1939 CAN communication with transmission control units:

- **Receive**: Torque requests from TCU (PGN 0xF003)
- **Transmit**: Torque status to TCU (PGN 0xCFE6)
- **Message validation**: Checksum and range checking
- **Timeout handling**: Fallback to pedal control if TCU communication fails

### Message Format

**TCU Torque Request (8 bytes)**:
- Bytes 0-1: Torque request (0.125 Nm/bit, signed)
- Byte 2: Priority level
- Byte 3: Control flags
- Bytes 4-5: Sequence number
- Bytes 6-7: Checksum

## Safety Features

### Multiple Protection Layers

1. **Sensor validation** - Invalid readings use cached values or fallbacks
2. **Range limiting** - Torque requests clamped to configured limits
3. **Rate limiting** - Prevents sudden torque changes
4. **Timeout protection** - Disables external control if communication fails
5. **Emergency shutdown** - Immediate disable on critical faults

### Fault Handling

- Sensor faults logged once to prevent spam
- Automatic fallback to safe values
- System health monitoring and reporting
- Graceful degradation when components fail

## Performance

### Timing Requirements

- **Fast callback**: 100Hz (10ms) - Main control loop
- **Slow callback**: 10Hz (100ms) - Diagnostics and CAN transmission
- **Control loop time**: < 100μs typical execution time

### Memory Usage

- **RAM**: ~2KB for tables and state variables
- **Flash**: ~8KB for code
- **Stack**: ~500 bytes maximum during execution

## Testing

### Unit Tests

Run the test suite to validate functionality:
```bash
make test_torque_control
```

Tests cover:
- Basic initialization and configuration
- Sensor validation and fault handling
- Torque model calculations
- Rate limiting and safety features
- CAN message processing
- Performance benchmarks

### Integration Testing

1. **Sensor validation**: Disconnect sensors and verify fallback behavior
2. **Rate limiting**: Apply sudden pedal inputs and verify smooth response
3. **Safety limits**: Request excessive torque and verify limiting
4. **CAN communication**: Send TCU messages and verify response

## Troubleshooting

### Common Issues

1. **System won't enable**
   - Check sensor availability with `torque_status`
   - Verify configuration limits are reasonable
   - Run `torque_enable` and check console output

2. **Poor throttle response**
   - Check `torqueRampRate` setting (too low = sluggish)
   - Verify pedal-to-torque table mapping
   - Monitor `torqueLimiterFlags` for active limits

3. **CAN communication issues**
   - Verify `enableTcuIntegration` is true
   - Check CAN bus termination and wiring
   - Monitor `tcuCommOk` status

### Debug Outputs

Enable debug logging to trace system behavior:
```cpp
#define TORQUE_DEBUG 1  // Add to global.h
```

This enables detailed logging of:
- Sensor readings and validation
- Torque calculations and limiting
- CAN message processing
- Performance timing

## Future Enhancements

### Planned Features

- **Traction control integration** - Wheel slip detection and torque reduction
- **Launch control** - RPM-based torque limiting for drag racing
- **Torque vectoring** - Individual wheel torque control for AWD systems
- **Machine learning** - Adaptive torque mapping based on driving patterns

### Expansion Points

The modular architecture allows easy addition of:
- Additional torque sources (cruise control, stability systems)
- More sophisticated torque models
- Advanced diagnostic features
- Custom calibration tools

## Support

For questions or issues:
1. Check this documentation first
2. Review console command output
3. Run unit tests to verify functionality
4. Post on rusEFI forums with detailed logs
