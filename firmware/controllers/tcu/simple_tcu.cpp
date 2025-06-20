#include "pch.h"

#include "simple_tcu.h"

#if EFI_TCU
SimpleTransmissionController simpleTransmissionController;

void SimpleTransmissionController::init() {
    for (size_t i = 0; i < efi::size(engineConfiguration->tcu_solenoid); i++) {
        enginePins.tcuSolenoids[i].initPin("Transmission Solenoid", engineConfiguration->tcu_solenoid[i], engineConfiguration->tcu_solenoid_mode[i]);
    }
}

void SimpleTransmissionController::update(gear_e gear) {
    for (size_t i = 0; i < efi::size(engineConfiguration->tcu_solenoid); i++) {
#if ! EFI_UNIT_TEST
			enginePins.tcuSolenoids[i].setValue(config->tcuSolenoidTable[i][static_cast<int>(gear) + 1]);
#endif
    }
    setCurrentGear(gear);

#if EFI_TUNER_STUDIO
    // if (engineConfiguration->debugMode == DBG_TCU) {
    //     engine->outputChannels.debugIntField1 = config->tcuSolenoidTable[static_cast<int>(gear) + 1][0];
    //     engine->outputChannels.debugIntField2 = config->tcuSolenoidTable[static_cast<int>(gear) + 1][1];
    //     engine->outputChannels.debugIntField3 = config->tcuSolenoidTable[static_cast<int>(gear) + 1][2];
    //     engine->outputChannels.debugIntField4 = config->tcuSolenoidTable[static_cast<int>(gear) + 1][3];
    //     engine->outputChannels.debugIntField5 = config->tcuSolenoidTable[static_cast<int>(gear) + 1][4];
    // }
#endif

		TransmissionControllerBase::update(gear);
}

SimpleTransmissionController* getSimpleTransmissionController() {
	return &simpleTransmissionController;
}
#endif // EFI_TCU
