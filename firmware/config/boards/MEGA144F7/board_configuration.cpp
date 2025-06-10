#include "pch.h"

Gpio getCommsLedPin() {
	return Gpio::Unassigned;
}

Gpio getRunningLedPin() {
	return Gpio::Unassigned;
}

Gpio getWarningLedPin() {
	return Gpio::Unassigned;
}


void setBoardDefaultConfiguration() {

    	engineConfiguration->analogInputDividerCoefficient = 1.47f;

	engineConfiguration->adcVcc = 3.3f;
	engineConfiguration->is_enabled_spi_3 = true;

}

bool isBoardAllowingLackOfPps() {
	return engineConfiguration->allowIdenticalPps;
}

