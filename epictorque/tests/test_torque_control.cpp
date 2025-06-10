/**
 * @file test_torque_control.cpp
 * @brief Unit tests for EpicTorque control system
 */

#include "pch.h"
#include "TorqueControl.h"
#include "torque_integration.h"

#if EFI_UNIT_TEST

#include "gtest/gtest.h"

class TorqueControlTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Initialize test environment
        initTorqueControlDefaults();
        
        // Set up mock sensors
        Sensor::setMockValue(SensorType::AcceleratorPedal, 0);
        Sensor::setMockValue(SensorType::Rpm, 1000);
        Sensor::setMockValue(SensorType::AirMass, 1.0f);
        Sensor::setMockValue(SensorType::Lambda1, 1.0f);
    }
    
    void TearDown() override {
        // Clean up
        disableTorqueControl();
    }
};

TEST_F(TorqueControlTest, BasicInitialization) {
    // Test that system initializes correctly
    EXPECT_FALSE(isTorqueControlEnabled()); // Should start disabled
    
    // Enable torque control
    EXPECT_TRUE(enableTorqueControl());
    EXPECT_TRUE(isTorqueControlEnabled());
    
    // Check default configuration
    auto& config = engineConfiguration->torqueConfig;
    EXPECT_GT(config.torqueRampRate, 0);
    EXPECT_GT(config.maxTorqueLimit, 0);
    EXPECT_LT(config.minTorqueLimit, 0);
}

TEST_F(TorqueControlTest, SensorValidation) {
    TorqueSensorManager sensorManager;
    
    // Test valid sensor reading
    Sensor::setMockValue(SensorType::AcceleratorPedal, 50.0f);
    float pedalValue = sensorManager.getValidatedSensor(SensorType::AcceleratorPedal, 0);
    EXPECT_FLOAT_EQ(pedalValue, 50.0f);
    EXPECT_TRUE(sensorManager.isSensorHealthy(SensorType::AcceleratorPedal));
    
    // Test invalid sensor reading
    Sensor::resetMockValue(SensorType::AcceleratorPedal);
    float fallbackValue = sensorManager.getValidatedSensor(SensorType::AcceleratorPedal, 25.0f);
    EXPECT_FLOAT_EQ(fallbackValue, 25.0f);
}

TEST_F(TorqueControlTest, TorqueModel) {
    RusEFITorqueModel model;
    
    // Test torque estimation with valid inputs
    float torque = model.estimateEngineTorque(1.5f, 25.0f, 1.0f, 2000.0f);
    EXPECT_GT(torque, 0); // Should produce positive torque
    EXPECT_LT(torque, 500); // Should be reasonable value
    
    // Test with zero RPM
    float zeroRpmTorque = model.estimateEngineTorque(1.5f, 25.0f, 1.0f, 0);
    EXPECT_FLOAT_EQ(zeroRpmTorque, 0); // Should be zero for stopped engine
}

TEST_F(TorqueControlTest, ActuatorControl) {
    TorqueActuatorController actuator;
    actuator.init();
    
    // Test basic torque to airmass conversion
    // This would require more detailed mocking of ETB system
    EXPECT_NO_THROW(actuator.setTargetTorque(100.0f, 90.0f, 2000.0f));
}

TEST_F(TorqueControlTest, PedalToTorqueMapping) {
    enableTorqueControl();
    
    // Test pedal mapping
    Sensor::setMockValue(SensorType::AcceleratorPedal, 0);
    torqueControlModule.onFastCallback();
    
    Sensor::setMockValue(SensorType::AcceleratorPedal, 50);
    torqueControlModule.onFastCallback();
    
    Sensor::setMockValue(SensorType::AcceleratorPedal, 100);
    torqueControlModule.onFastCallback();
    
    // Verify outputs are reasonable
    auto& outputs = engine->outputChannels.torque;
    EXPECT_GE(outputs.targetTorque, 0);
    EXPECT_LE(outputs.targetTorque, engineConfiguration->torqueConfig.maxTorqueLimit);
}

TEST_F(TorqueControlTest, RateLimiting) {
    enableTorqueControl();
    
    // Set aggressive ramp rate for testing
    engineConfiguration->torqueConfig.torqueRampRate = 100.0f; // Nm/s
    
    // Sudden pedal input
    Sensor::setMockValue(SensorType::AcceleratorPedal, 0);
    torqueControlModule.onFastCallback();
    float initialTorque = engine->outputChannels.torque.targetTorque;
    
    Sensor::setMockValue(SensorType::AcceleratorPedal, 100);
    torqueControlModule.onFastCallback();
    float limitedTorque = engine->outputChannels.torque.targetTorque;
    
    // Should be rate limited
    EXPECT_LT(limitedTorque - initialTorque, 10.0f); // 100 Nm/s * 0.01s = 1 Nm max change
}

TEST_F(TorqueControlTest, SafetyLimits) {
    enableTorqueControl();
    
    // Test maximum torque limiting
    engineConfiguration->torqueConfig.maxTorqueLimit = 150.0f;
    
    // Request excessive torque via pedal mapping
    for (int i = 0; i < PEDAL_TO_TORQUE_SIZE; i++) {
        engineConfiguration->torqueConfig.pedalToTorqueTable[i] = 300.0f; // Excessive
    }
    
    Sensor::setMockValue(SensorType::AcceleratorPedal, 100);
    torqueControlModule.onFastCallback();
    
    // Should be limited to max
    EXPECT_LE(engine->outputChannels.torque.targetTorque, 150.0f);
    EXPECT_TRUE(engine->outputChannels.torque.torqueLimiterFlags & TORQUE_LIMIT_MAX_TORQUE);
}

TEST_F(TorqueControlTest, CANIntegration) {
    enableTorqueControl();
    engineConfiguration->torqueConfig.enableTcuIntegration = true;
    
    // Simulate TCU torque request
    CANRxFrame frame;
    frame.DLC = 8;
    frame.data8[0] = 0x00; // 100 Nm * 8 = 800 raw
    frame.data8[1] = 0x03; // (800 >> 8) = 3
    frame.data8[2] = 0x01; // Priority
    frame.data8[3] = 0x00; // Flags
    frame.data8[4] = 0x01; // Sequence low
    frame.data8[5] = 0x00; // Sequence high
    frame.data8[6] = 0x02; // Checksum low (800 ^ 1 ^ 0 ^ 1 = 802)
    frame.data8[7] = 0x03; // Checksum high
    
    torqueControlModule.getCanManager().processTCURequest(frame);
    
    // Should accept TCU request
    EXPECT_TRUE(torqueControlModule.tcuRequestActive);
    EXPECT_FLOAT_EQ(torqueControlModule.tcuTorqueRequest, 100.0f);
}

TEST_F(TorqueControlTest, DiagnosticOutputs) {
    enableTorqueControl();
    
    // Run control cycle
    torqueControlModule.onFastCallback();
    torqueControlModule.onSlowCallback();
    
    // Check diagnostic outputs are populated
    auto& outputs = engine->outputChannels.torque;
    EXPECT_TRUE(outputs.torqueControlActive);
    EXPECT_GE(outputs.controlFrequency, 0);
    EXPECT_GE(outputs.pedalPosition, 0);
    EXPECT_GE(outputs.engineRpm, 0);
}

// Performance test
TEST_F(TorqueControlTest, PerformanceBenchmark) {
    enableTorqueControl();
    
    auto start = getTimeNowNt();
    
    // Run 1000 control cycles
    for (int i = 0; i < 1000; i++) {
        torqueControlModule.onFastCallback();
    }
    
    auto end = getTimeNowNt();
    float totalTime = NT2USF(end - start);
    float avgTime = totalTime / 1000.0f;
    
    // Should complete in reasonable time (< 100μs per cycle)
    EXPECT_LT(avgTime, 100.0f);
    
    efiPrintf("EpicTorque performance: %.1f μs/cycle", avgTime);
}

#endif // EFI_UNIT_TEST
