#include "pch.h"
#include "M144_meta.h"

Gpio getCommsLedPin() {
	return Gpio::Unassigned;
}

Gpio getRunningLedPin() {
	return Gpio::Unassigned;
}

Gpio getWarningLedPin() {
	return Gpio::Unassigned;
}

// board-specific configuration setup
void setBoardDefaultConfiguration() {
   	engineConfiguration->analogInputDividerCoefficient = 1.47f;
	engineConfiguration->adcVcc = 3.3f;
	engineConfiguration->is_enabled_spi_3 = true;
}

bool isBoardAllowingLackOfPps() {
	return engineConfiguration->allowIdenticalPps;
}

#include "connectors/generated_outputs.h"

int getBoardMetaOutputsCount() {
	return efi::size(GENERATED_OUTPUTS);
}

int getBoardMetaLowSideOutputsCount() {
	return getBoardMetaOutputsCount() - 16;
}

Gpio* getBoardMetaOutputs() {
	return GENERATED_OUTPUTS;
}


int getBoardMetaDcOutputsCount() {
	return 2;
}
