/**
 * @file        lps25.cpp
 * @brief       Driver for the ST LPS25HB pressure sensor
 *
 * At the moment uses bit-banged I2C driver
 *
 * @date February 6, 2020
 * @author Matthew Kennedy, (c) 2020
 */

#include "pch.h"

#include "lps25.h"

static constexpr uint8_t check_addr1 = 0x5C;
static constexpr uint8_t check_addr2 = 0x5D;
static constexpr uint8_t expectedWhoAmILps22 = 0xB1;
static constexpr uint8_t expectedWhoAmILps25 = 0xBD;
static constexpr uint8_t expectedWhoAmILps22HHTR = 0xB3;
uint8_t addr;


// Control register 1
#define LPS_CR1_PD (1 << 7)
#define LPS22_CR1_ODR_25hz (3 << 4) // 25 hz
#define LPS25_CR1_ODR_25hz (4 << 4) // 25 hz
#define LPS_CR1_BDU (1 << 1) //

// Status register flags
#define LPS22_SR_P_DA 1		     // Pressure data available
#define LPS25_SR_P_DA 1 << 1	// Pressure data available LPS25

#define REG_WhoAmI 0x0F

// register address different on LPS22 vs LPS25
#define REG_Cr1_Lps22 0x10
#define REG_Cr1_Lps25 0x20
#define REG_Status 0x27
#define REG_PressureOutXl 0x28
#define REG_PressureOutL 0x29
#define REG_PressureOutH 0x2A

bool Lps25::init(brain_pin_e scl, brain_pin_e sda) {
	uint8_t cr1;
	if (!m_i2c.init(scl, sda)) {
		return false;
	}

    // check 0x5c first
	auto whoAmI = m_i2c.readRegister(check_addr1, REG_WhoAmI);
    if (whoAmI != 255) {
		addr = check_addr1;
        efiPrintf("I2C baro: found baro on addr %d = %d", addr, whoAmI);
    }

	if (whoAmI == 255) {
          whoAmI = m_i2c.readRegister(check_addr2, REG_WhoAmI);
          if (whoAmI != 255) {
         	addr = check_addr2;
			efiPrintf("I2C baro: found baro on addr %d = %d", addr, whoAmI);
          }
	}

	// Read ident register

	switch (whoAmI)
	{
    case expectedWhoAmILps22HHTR:
      	m_type = Type::Lps22HHTR;
        break;
	case expectedWhoAmILps22:
		m_type = Type::Lps22;
		break;
	case expectedWhoAmILps25:
		m_type = Type::Lps25;
		break;
	default:
		// chip not detected
		return false;
	}

	cr1 =
		LPS22_CR1_ODR_25hz |	// 25hz update rate
		// TODO: should bdu be set?
		LPS_CR1_BDU;		// Output registers update only when read

	if (m_type == Type::Lps25) {
		 cr1 =
			LPS22_CR1_ODR_25hz |	// 25hz update rate
			LPS_CR1_BDU | // ;		// Output registers update only when read
		// Set to active mode
		// this bit must be 0 on LPS22
            LPS_CR1_PD;
	}

	// Set the control registers
	m_i2c.writeRegister(addr, regCr1(), cr1);

	m_hasInit = true;
	return true;
}

expected<float> Lps25::readPressureKpa() {
	if (!m_hasInit) {
		return unexpected;
	}

	uint8_t buffer[4];
	// Sequential multi-byte reads need to set the high bit of the
	// register address to enable multi-byte read
	constexpr uint8_t readAddr = REG_Status | 0x80;
	m_i2c.writeRead(addr, &readAddr, 1, buffer, 4);

	// First check the status reg to check if there are data available

	bool hasPressure;


	if (m_type == Type::Lps25) {
		hasPressure = buffer[0] & LPS25_SR_P_DA;
	}  else {
		hasPressure = buffer[0] & LPS22_SR_P_DA;
	}

	if (!hasPressure) {
		if (engine->outputChannels.baroHasNoPressure > 250) {
			engine->outputChannels.baroHasNoPressure = 0;
		}
		engine->outputChannels.baroHasNoPressure++;

		return unexpected;
	}

	if (engine->outputChannels.baroHasPressure > 250) {
		engine->outputChannels.baroHasPressure = 0;
	}
	engine->outputChannels.baroHasPressure++;

	// Glue the 3 bytes back in to a 24 bit integer
	uint32_t counts = buffer[3] << 16 | buffer[2] << 8 | buffer[1];

	engine->outputChannels.baroCounts = counts;

	// 4096 counts per hectopascal
	// = 40960 counts per kilopascal
	constexpr float ratio = 1 / 40960.0f;
	
	float kilopascal = counts * ratio;

	// Sensor limits are 26-126 kPa
	// The highest ever barometric pressure measured was only 108.3 kPa
	// The pressure at the highest altitude road (Khardung La, India/Tibet) is at 5600 meters,
	// which should have a nominal barometric pressure of around 50 kPa
	// Anything outside that range is not a place we expect your engine to run, so we assume
	// some sensing problem (sealed ECU case and high temperature?)
	if (kilopascal > 120 || kilopascal < 50) {
		return unexpected;
	}

	return kilopascal;
}

uint8_t Lps25::regCr1() const {
	switch (m_type)
	{
	case Type::Lps22HHTR:
	case Type::Lps22:
		return REG_Cr1_Lps22;
	case Type::Lps25:
	default:
		return REG_Cr1_Lps25;
	}
}
