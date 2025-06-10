#include "pch.h"
#include "defaults.h"
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


// this method is useful for desperate time debugging or hardware validation
static void M144SetPinValue(const char *pinName, int bit) {
	brain_pin_e pin = parseBrainPin(pinName);
	if (pin == Gpio::Invalid) {
		return;
	}
	efiSetPadModeWithoutOwnershipAcquisition("bench_pin_test", pin, PAL_LOW);
	// low-level API which does not care about 'qcDirectPinControlMode'
	palWritePad(getHwPort("write", pin), getHwPin("write", pin), bit);
}

void boardInitHardware() {
	const char *INITLOW[] = { "PE10"  };
	size_t init_initlow = 1;
	for (size_t i=0;i<init_initlow;i++){
		M144SetPinValue(INITLOW[i], 0);
	}
}