#include "pch.h"
#include "defaults.h"
#include "epicECU_meta.h"

// extern OutputPin accelerometerChipSelect;
#define SID_EN Gpio::B9
#define SID_EN_PIN_TEXT "PB9"

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
// one time setup
void setBoardDefaultConfiguration() {
	engineConfiguration->map.sensor.hwChannel = EFI_ADC_6;
	engineConfiguration->clt.adcChannel = EFI_ADC_13;
	engineConfiguration->iat.adcChannel = EFI_ADC_11;
	engineConfiguration->tps1_1AdcChannel = EFI_ADC_1;
	engineConfiguration->tps1_2AdcChannel = EFI_ADC_0;
	engineConfiguration->throttlePedalPositionAdcChannel = EFI_ADC_2;
	engineConfiguration->throttlePedalPositionSecondAdcChannel = EFI_ADC_7;
	engineConfiguration->adcVcc = 3.3f;
    engineConfiguration->analogInputDividerCoefficient = 2.0f;
    engineConfiguration->vbattDividerCoeff = 8.8f;
    engineConfiguration->alwaysInstantRpm = 1;
    engineConfiguration->allowDFUwithIgn = 1;
	engineConfiguration->is_enabled_spi_1 = 1;
    engineConfiguration->is_enabled_spi_2 = 1;
    engineConfiguration->isSdCardEnabled = 1;
    engineConfiguration->alwaysWriteSdCard = 1;
	engineConfiguration->etbFunctions[1] = DC_None;



    // actually can3 by the spec sheet, maybe fine ?
	engineConfiguration->can2TxPin = Gpio::A15;
	engineConfiguration->can2RxPin = Gpio::A8;


	engineConfiguration->is_enabled_spi_1 = true;


	engineConfiguration->clt.config.bias_resistor = 2490;
	engineConfiguration->iat.config.bias_resistor = 2490;


	engineConfiguration->isFasterEngineSpinUpEnabled = true;
	engineConfiguration->alwaysInstantRpm = true;



	engineConfiguration->tunerStudioSerialSpeed = 115200;
	engineConfiguration->etbFunctions[1] = DC_None;

	engineConfiguration->calmerBurn = true;
	engineConfiguration->afrSensorLambdaRange = false;
	engineConfiguration->tcUseIgnTiming = true;
	engineConfiguration->tcUseSparkSkip = true;
	engineConfiguration->tcUseETB = true;
	engineConfiguration->STFTResetRegionChange = true;
	engineConfiguration->disableEGT = false;
	engineConfiguration->epicInitHSHigh = true;
	engineConfiguration->flexEnabled = false;
	engineConfiguration->disableBARO = false;
	engineConfiguration->noFastMap = true;
	engineConfiguration->disableMapAveraging = true;
	engineConfiguration->disableAdcBiquadFilter = false;

    config->mapLowPassCutoffHz = 10;
    config->mafLowPassCutoffHz = 10;
    config->auxLowPassCutoffHz = 10;
    config->ppsLowPassCutoffHz = 10;
    config->egoLowPassCutoffHz = 10;
    config->tpsLowPassCutoffHz = 100;
	engineConfiguration->accelEnX = 1;
	engineConfiguration->accelEnY = 1;
	engineConfiguration->accelEnZ = 1;

	engineConfiguration->accelHighRes = 1;
	engineConfiguration->disableProgOutputs = 0;
	engineConfiguration->disableMCP3208 = 0;
	engineConfiguration->disableINJOK = 0;
	engineConfiguration->disableDINP = 0;

	engineConfiguration->enableSlipCalculations = 1;
    engineConfiguration->accelerometerScale = 0;
	engineConfiguration->accelerometerFds = 0;
	engineConfiguration->accelerometerHPCF = 0;
	engineConfiguration->accelerometerHPM = 0;
	engineConfiguration->accelerometerOrd = 5;
	engineConfiguration->accelSelfTest = 0;

	engineConfiguration->driveWheelRevPerKm1 = 100;
	engineConfiguration->driveWheelRevPerKm2 = 100;
	engineConfiguration->driveWheelRevPerKm3 = 100;
	engineConfiguration->driveWheelRevPerKm4 = 100;

	engineConfiguration->wallWettingAeEnabled = 1;
	engineConfiguration->useMapEstimateDuringTransient = 1;
	engineConfiguration->allowDFUwithIgn = 1;



}

// these are overrides
void setBoardConfigOverrides() {


	engineConfiguration->canTxPin = Gpio::D1;
	engineConfiguration->canRxPin = Gpio::D0;

    engineConfiguration->lps25BaroSensorScl = Gpio::B6;
	engineConfiguration->lps25BaroSensorSda = Gpio::B7;

    engineConfiguration->flexSensorPin = Gpio::EPICECU_FLEX;

	engineConfiguration->vbattAdcChannel = EFI_ADC_9;

	setupTLE9201IncludingStepper(/*PWM controlPin*/Gpio::J10, Gpio::J9, Gpio::J11);
	setupTLE9201IncludingStepper(/*PWM controlPin*/Gpio::J7, Gpio::J6, Gpio::J8, 1);


#ifdef TS_SECONDARY_UxART_PORT
	engineConfiguration->binarySerialTxPin = Gpio::B10;
	engineConfiguration->binarySerialRxPin = Gpio::B11;
#endif // TS_SECONDARY_UxART_PORT

	engineConfiguration->sdCardCsPin = Gpio::B12;
	engineConfiguration->sdCardSpiDevice = SPI_DEVICE_2;
	engineConfiguration->spi2mosiPin = Gpio::B15;
	engineConfiguration->spi2misoPin = Gpio::B14;
	engineConfiguration->spi2sckPin  = Gpio::B13;


	config->mcp3208spidevice = SPI_DEVICE_1;
	engineConfiguration->spi1mosiPin = Gpio::B5;
	engineConfiguration->spi1misoPin = Gpio::B4;
	engineConfiguration->spi1sckPin  = Gpio::B3;
	config->mcp3208spidevice_1cs = Gpio::D12;
	config->mcp3208spidevice_2cs = Gpio::D14;
	config->mcp3208spidevice_3cs = Gpio::D13;
	config->mcp3208vref = 3.3f;
	config->mcp3208divider = 2.0f;

	engineConfiguration->max31855_cs[0] = Gpio::B8;
	engineConfiguration->max31855_cs[1] = Gpio::G15;
	engineConfiguration->max31855_cs[2] = Gpio::K7;
	engineConfiguration->max31855_cs[3] = Gpio::K6;
	engineConfiguration->max31855_cs[4] = Gpio::K5;
	engineConfiguration->max31855_cs[5] = Gpio::K4;
	engineConfiguration->max31855_cs[6] = Gpio::K3;
	engineConfiguration->max31855_cs[7] = Gpio::G14;
	engineConfiguration->max31855spiDevice = SPI_DEVICE_1;
	engineConfiguration->accelerometerSpiDevice = SPI_DEVICE_1;
    engineConfiguration->accelerometerCsPin = Gpio::D15;



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

void updateEpicDigitalInputs(void) {
	// read status of injector ok
                if (!engineConfiguration->disableINJOK) {

	engine->outputChannels.inj1ok = efiReadPin(Gpio::D8);
	engine->outputChannels.inj2ok = efiReadPin(Gpio::D10);
	engine->outputChannels.inj3ok = efiReadPin(Gpio::H7);
	engine->outputChannels.inj4ok = efiReadPin(Gpio::H8);
	engine->outputChannels.inj5ok = efiReadPin(Gpio::J5);
	engine->outputChannels.inj6ok = efiReadPin(Gpio::H6);
	engine->outputChannels.inj7ok = efiReadPin(Gpio::H10);
	engine->outputChannels.inj8ok = efiReadPin(Gpio::H9);
	engine->outputChannels.inj9ok = efiReadPin(Gpio::H11);
	engine->outputChannels.inj10ok = efiReadPin(Gpio::H12);
	engine->outputChannels.inj11ok = efiReadPin(Gpio::D9);
	engine->outputChannels.inj12ok = efiReadPin(Gpio::D11);
        	}

//	uint8_t epic_dinps18
        if (!engineConfiguration->disableDINP) {
	engine->outputChannels.epic_dinp1 = efiReadPin(Gpio::C13);
	engine->outputChannels.epic_dinp2 = efiReadPin(Gpio::E6);
	engine->outputChannels.epic_dinp3 = efiReadPin(Gpio::E5);
	engine->outputChannels.epic_dinp4 = efiReadPin(Gpio::E4);
	engine->outputChannels.epic_dinp5 = efiReadPin(Gpio::E3);
	engine->outputChannels.epic_dinp6 = efiReadPin(Gpio::E2);
	engine->outputChannels.epic_dinp7 = efiReadPin(Gpio::E1);
	engine->outputChannels.epic_dinp8 = efiReadPin(Gpio::E0);
	engine->outputChannels.epic_dinps18 = (engine->outputChannels.epic_dinp1 << 0) +
                                          (engine->outputChannels.epic_dinp2 << 1) +
                                          (engine->outputChannels.epic_dinp3 << 2) +
                                          (engine->outputChannels.epic_dinp4 << 3) +
                                          (engine->outputChannels.epic_dinp5 << 4) +
                                          (engine->outputChannels.epic_dinp6 << 5) +
                                          (engine->outputChannels.epic_dinp7 << 6) +
                                          (engine->outputChannels.epic_dinp8 << 7);


//  uint8_t epic_hall_inps18
	engine->outputChannels.epic_hall_inp1 = efiReadPin(Gpio::I13);
	engine->outputChannels.epic_hall_inp2 = efiReadPin(Gpio::I12);
	engine->outputChannels.epic_hall_inp3 = efiReadPin(Gpio::I11);
	engine->outputChannels.epic_hall_inp4 = efiReadPin(Gpio::I10);
	engine->outputChannels.epic_hall_inp5 = efiReadPin(Gpio::I9);
	engine->outputChannels.epic_hall_inp6 = efiReadPin(Gpio::I8);
	engine->outputChannels.epic_hall_inp7 = efiReadPin(Gpio::I7);
	engine->outputChannels.epic_hall_inp8 = efiReadPin(Gpio::I6);
	engine->outputChannels.epic_hall_inp9 = efiReadPin(Gpio::I5);
	engine->outputChannels.epic_hall_inp10 = efiReadPin(Gpio::I4);
	engine->outputChannels.epic_hall_inps18 = (engine->outputChannels.epic_hall_inp1 << 0) +
											  (engine->outputChannels.epic_hall_inp2 << 1) +
											  (engine->outputChannels.epic_hall_inp3 << 2) +
											  (engine->outputChannels.epic_hall_inp4 << 3) +
											  (engine->outputChannels.epic_hall_inp5 << 4) +
											  (engine->outputChannels.epic_hall_inp6 << 5) +
											  (engine->outputChannels.epic_hall_inp7 << 6) +
											  (engine->outputChannels.epic_hall_inp8 << 7);

	engine->outputChannels.epic_hall_inps916 = (engine->outputChannels.epic_hall_inp9  << 0) +
        									   (engine->outputChannels.epic_hall_inp10 << 1);
        }


}

void boardPeriodicSlowCallback() {
	updateEpicDigitalInputs();
}

// this method is useful for desperate time debugging or hardware validation
static void epicSetPinValue(const char *pinName, int bit) {
	brain_pin_e pin = parseBrainPin(pinName);
	if (pin == Gpio::Invalid) {
		return;
	}
	efiSetPadModeWithoutOwnershipAcquisition("bench_pin_test", pin, PAL_MODE_OUTPUT_PUSHPULL);
	// low-level API which does not care about 'qcDirectPinControlMode'
	palWritePad(getHwPort("write", pin), getHwPin("write", pin), bit);
}


static void startInputPinIfValid(const char *msg, brain_pin_e pin, pin_input_mode_e mode) {
	efiSetPadMode(msg, pin, getInputMode(mode));
}

void boardInitHardware() {
  	// set sid_en to low
 	epicSetPinValue(SID_EN_PIN_TEXT, 0);

	// set all of the CS on spi1 we have to high
	const char *SPI1_CS[] = { "PD15" , "PK3", "PK4", "PK5", "PK6", "PK7", "PB8", "PG15", "PG14", "PD12", "PD13", "PD14" };
    size_t quiet_spi = 12;
	for (size_t i=0;i<quiet_spi;i++ ){
          epicSetPinValue(SPI1_CS[i], 1);
    }

  	// injok pins
	startInputPinIfValid("inj1ok",(Gpio::D8),       PI_DEFAULT);
	startInputPinIfValid("inj2ok",(Gpio::D10),      PI_DEFAULT);
	startInputPinIfValid("inj3ok",(Gpio::H7) ,      PI_DEFAULT);
	startInputPinIfValid("inj4ok",(Gpio::H8),       PI_DEFAULT);
	startInputPinIfValid("inj5ok",(Gpio::J5),       PI_DEFAULT);
	startInputPinIfValid("inj6ok",(Gpio::H6),       PI_DEFAULT);
	startInputPinIfValid("inj7ok",(Gpio::H10),      PI_DEFAULT);
	startInputPinIfValid("inj8ok",(Gpio::H9),       PI_DEFAULT);
	startInputPinIfValid("inj9ok",(Gpio::H11),      PI_DEFAULT);
	startInputPinIfValid("inj10ok",(Gpio::H12),     PI_DEFAULT);
	startInputPinIfValid("inj11ok",(Gpio::D9),      PI_DEFAULT);
	startInputPinIfValid("inj12ok",(Gpio::D11),     PI_DEFAULT);

	efiSetPadModeWithoutOwnershipAcquisition("dinp C13", Gpio::C13, PI_DEFAULT);
	efiSetPadModeWithoutOwnershipAcquisition("dinp E6 ", Gpio::E6 , PI_DEFAULT);
	efiSetPadModeWithoutOwnershipAcquisition("dinp E5 ", Gpio::E5 , PI_DEFAULT);
	efiSetPadModeWithoutOwnershipAcquisition("dinp E4 ", Gpio::E4 , PI_DEFAULT);
	efiSetPadModeWithoutOwnershipAcquisition("dinp E3 ", Gpio::E3 , PI_DEFAULT);
	efiSetPadModeWithoutOwnershipAcquisition("dinp E2 ", Gpio::E2 , PI_DEFAULT);
	efiSetPadModeWithoutOwnershipAcquisition("dinp E1 ", Gpio::E1 , PI_DEFAULT);
	efiSetPadModeWithoutOwnershipAcquisition("dinp E0 ", Gpio::E0 , PI_DEFAULT);
	efiSetPadModeWithoutOwnershipAcquisition("dinp I13", Gpio::I13, PI_DEFAULT);
	efiSetPadModeWithoutOwnershipAcquisition("dinp I12", Gpio::I12, PI_DEFAULT);
	efiSetPadModeWithoutOwnershipAcquisition("dinp I11", Gpio::I11, PI_DEFAULT);
	efiSetPadModeWithoutOwnershipAcquisition("dinp I10", Gpio::I10, PI_DEFAULT);
	efiSetPadModeWithoutOwnershipAcquisition("dinp I9 ", Gpio::I9 , PI_DEFAULT);
	efiSetPadModeWithoutOwnershipAcquisition("dinp I8 ", Gpio::I8 , PI_DEFAULT);
	efiSetPadModeWithoutOwnershipAcquisition("dinp I7 ", Gpio::I7 , PI_DEFAULT);
	efiSetPadModeWithoutOwnershipAcquisition("dinp I6 ", Gpio::I6 , PI_DEFAULT);
	efiSetPadModeWithoutOwnershipAcquisition("dinp I5 ", Gpio::I5 , PI_DEFAULT);
	efiSetPadModeWithoutOwnershipAcquisition("dinp I4 ", Gpio::I4 , PI_DEFAULT);



  if (engineConfiguration->epicInitHSHigh) {
    const char *INITHIGH[] = { "PD2" , "PD7", "PC12", "PC11"  };
	size_t init_highcnt = 4;
    for (size_t i=0;i<init_highcnt;i++){
        epicSetPinValue(INITHIGH[i], 1);
    }
  }
}


// injok pins
void boardStopHardware() {
	brain_pin_markUnused((Gpio::D8)   );
	brain_pin_markUnused((Gpio::D10)  );
	brain_pin_markUnused((Gpio::H7)   );
	brain_pin_markUnused((Gpio::H8)   );
	brain_pin_markUnused((Gpio::J5)   );
	brain_pin_markUnused((Gpio::H6)   );
	brain_pin_markUnused((Gpio::H10)  );
	brain_pin_markUnused((Gpio::H9)   );
	brain_pin_markUnused((Gpio::H11)  );
	brain_pin_markUnused((Gpio::H12)  );
	brain_pin_markUnused((Gpio::D9)   );
	brain_pin_markUnused((Gpio::D11)  );

	brain_pin_markUnused((Gpio::C13)  );
	brain_pin_markUnused((Gpio::E6 )  );
	brain_pin_markUnused((Gpio::E5 )  );
	brain_pin_markUnused((Gpio::E4 )  );
	brain_pin_markUnused((Gpio::E3 )  );
	brain_pin_markUnused((Gpio::E2 )  );
	brain_pin_markUnused((Gpio::E1 )  );
	brain_pin_markUnused((Gpio::E0 )  );
	brain_pin_markUnused((Gpio::I13)  );
	brain_pin_markUnused((Gpio::I12)  );
	brain_pin_markUnused((Gpio::I11)  );
	brain_pin_markUnused((Gpio::I10)  );
	brain_pin_markUnused((Gpio::I9 )  );
	brain_pin_markUnused((Gpio::I8 )  );
	brain_pin_markUnused((Gpio::I7 )  );
	brain_pin_markUnused((Gpio::I6 )  );
	brain_pin_markUnused((Gpio::I5 )  );
	brain_pin_markUnused((Gpio::I4 )  );


}