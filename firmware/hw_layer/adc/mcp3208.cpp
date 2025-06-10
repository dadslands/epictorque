/*
yolo
 */

#include "pch.h"

#include "gpio_ext.h"

#include "mcp3208.h"

#if EFI_MCP_3208 && !EFI_SIMULATOR

#if EFI_MCP_3208 && !EFI_SIMULATOR

/*==========================================================================*/
/* Driver local definitions.												*/
/*==========================================================================*/

void init_lis3dh(void);

#define DRIVER_NAME				"mcp3208"


static bool drv_task_ready = false;

// struct mcp3208_config mcp3208_1;

typedef enum {
	MCP3208_DISABLED = 0,
	MCP3208_WAIT_INIT,
	MCP3208_READY,
	MCP3208_FAILED
} mcp3208_drv_state;

#ifdef STM32H7XX
// H7 SPI clock is set to 80MHz
// fast mode is 80mhz/2 = 40MHz

SPIConfig spicfg3208 = {
		.circular = false,
		.end_cb = NULL,
		.ssport = nullptr,
		.sspad = 0,
      .cfg1 =  SPI_CFG1_MBR_DIV64 | SPI_CFG1_DSIZE_VALUE(7),
		// .cfg1 = 7 // 8 bits per byte
		// 	| SPI_CFG1_MBR_DIV128  MBR = 001, divider = 4
		.cfg2 = 0
};

#else // Not H7, ie F4/F7

// 168mhz F4: 42 or 21 MHz depending on which SPI device
// 216mhz F7: 54 or 27 MHz depending on whcih SPI device

SPIConfig spicfg3208 = {
		.circular = false,
		.end_cb = NULL,
		.ssport = nullptr,
		.sspad = 0,
//  SPI_CR1_BR_1 | SPI_CR1_CPOL | SPI_CR1_CPHA  - ---- | SPI_CR1_CPOL
    	.cr1 =  (SPI_CR1_BR_2 | SPI_CR1_BR_0 ),
 	    .cr2 = SPI_CR2_8BIT_MODE
};


SPIConfig accelerometerSpiCfg = {
	.circular = FALSE,
	.end_cb = NULL,
	.ssport = NULL,
	.sspad = 0,
	.cr1 = SPI_CR1_BR_2 | SPI_CR1_BR_0 | SPI_CR1_BR_1 | SPI_CR1_CPOL | SPI_CR1_CPHA |
		SPI_CR1_8BIT_MODE | SPI_CR1_MSTR |
			 SPI_CR1_SSM | // Software Slave Management, the SSI bit will be internal reference
			 SPI_CR1_SSI // Internal Slave Select (active low) set High
	,
	.cr2 = SPI_CR2_8BIT_MODE | SPI_CR2_SSOE
};

//SPIConfig egtSpiCfg = {
//	.circular = FALSE,
//	.end_cb = NULL,
//	.ssport = NULL,
//	.sspad = 0,
//	.cr1 = SPI_CR1_BR_2 | SPI_CR1_BR_0 | SPI_CR1_BR_1 | SPI_CR1_CPOL | SPI_CR1_CPHA |
//		SPI_CR1_8BIT_MODE | SPI_CR1_MSTR |
//			 SPI_CR1_SSM | // Software Slave Management, the SSI bit will be internal reference
//			 SPI_CR1_SSI // Internal Slave Select (active low) set High
//	,
//	.cr2 = SPI_CR2_8BIT_MODE | SPI_CR2_SSOE
//};



#endif


/* OS */
SEMAPHORE_DECL(mcp3208_wake, 10 /* or BOARD_MCP3208_COUNT ? */);
static THD_WORKING_AREA(mcp3208_thread_1_wa, 256);

/* Driver */
struct Mcp3208 : public GpioChip {
	int init() override;

   	int readPad(size_t pin) {
   		// gpio read stuff
    	return MCP3208_analogRead(pin);
    }

	// Internal helpers
	int chip_init();

	// void spi_send(uint16_t tx);

	void update_outputs();
	int wake_driver();

  	void MCP3208_read_all_chan(void);

	uint16_t MCP3208_analogRead(uint8_t pin);


        size_t idx;
  	void mcp3208_read_0(void);
  	void mcp3208_read_1(void);
  	void SPIReadRegister(uint16_t reg, size_t n, uint8_t* b);

	mcp3208_config		cfg;
	/* cached output state - state last send to chip */
	uint16_t					o_state_cached;
	/* state to be sended to chip */
	uint16_t					o_state;

  	uint16_t chanval[8];

  	uint8_t txbuf[3];
  	uint8_t rxbuf[3];

	mcp3208_drv_state			drv_state;
};

static Mcp3208 chips[BOARD_MCP3208_COUNT];

static const char* mcp3208_pin_names[8*3] = {
	"mcp3208_1.ADCH1",	"mcp3208_1.ADCH2",	"mcp3208_1.ADCH3",	 "mcp3208_1.ADCH4",	 "mcp3208_1.ADCH5",	"mcp3208_1.ADCH6", "mcp3208_1.ADCH7", "mcp3208_1.ADCH8",
	"mcp3208_2.ADCH1",	"mcp3208_2.ADCH2",	"mcp3208_2.ADCH3",	 "mcp3208_2.ADCH4",	 "mcp3208_2.ADCH5",	"mcp3208_2.ADCH6", "mcp3208_2.ADCH7", "mcp3208_2.ADCH8",
	"mcp3208_3.ADCH1",	"mcp3208_3.ADCH2",	"mcp3208_3.ADCH3",	 "mcp3208_3.ADCH4",	 "mcp3208_3.ADCH5",	"mcp3208_3.ADCH6", "mcp3208_3.ADCH7", "mcp3208_3.ADCH8"
};


// driver lis3dh
struct lis3dh_t  {
	void init();
	uint8_t whoami(void);
	void writeRegister(uint8_t reg, uint8_t write_buf_size, uint8_t *write_buffer );
	void readRegister(uint8_t reg, uint8_t bytes_to_read_after_write, uint8_t *read_buffer );
	void setFreq(void);
	void readData(void);
	lis3dh_config		cfg;
	bool initialized;
};


static lis3dh_t lis3dh;

//// driver MAX31855KASAT
//struct MAX31855KASAT_t  {
//	void init();
//	uint8_t whoami(void);
//	void writeRegister(uint8_t reg, uint8_t write_buf_size, uint8_t *write_buffer );
//	void readRegister(uint8_t reg, uint8_t bytes_to_read_after_write, uint8_t *read_buffer );
//	void setFreq(void);
//	void readData(void);
//	MAX31855KASAT_config		cfg;
//	bool initialized;
//};
//
//
//static MAX31855KASAT_t MAX31855KASAT[MAX31855KASAT_COUNT];



/*==========================================================================*/
/* Driver local functions.													*/
/*==========================================================================*/

/**
 * @brief MCP3208 send routine.
 * @details Sends 8. CS asserted before and released after transaction.
 */


void Mcp3208::mcp3208_read_0(void) {
  uint16_t tmp;
  printSpiConfig("mcp3208", config->mcp3208spidevice);
	efiPrintf("mcp3208 clock %d Hz", spiGetBaseClock(cfg.spi_bus) / (2 << ((cfg.spi_config.cr1 & SPI_CR1_BR_Msk) >> SPI_CR1_BR_Pos)));
	tmp = MCP3208_analogRead(2);
        efiPrintf("read0: %d", tmp);
}

void Mcp3208::mcp3208_read_1(void) {
    efiPrintf("MCP3208 ret: %d", MCP3208_analogRead(1));
}


void Mcp3208::SPIReadRegister(uint16_t reg, size_t n, uint8_t* b) {
  txbuf[0] = reg >> 8;
  txbuf[1] = reg & 0xff;
  txbuf[2] = 0;

  initSpiCsNoOccupy(&(cfg.spi_config), cfg.cs);

  spiAcquireBus(cfg.spi_bus);
  spiStart(cfg.spi_bus, &(cfg.spi_config));
  spiSelect(cfg.spi_bus);
  for (size_t i=0;i<n;i++) {
    b[i] = spiPolledExchange(cfg.spi_bus, txbuf[i]);
  }

  spiUnselect(cfg.spi_bus);
  spiStop(cfg.spi_bus);
  spiReleaseBus(cfg.spi_bus);
}

void Mcp3208::MCP3208_read_all_chan(void) {
  float div = config->mcp3208divider;

    for (size_t i=0;i<8;i++) {
      	if (div == 0) {
        	div = 1;
        }
       	engine->outputChannels.rawMCP3208_v_[((idx * 8) + i)] =  ((config->mcp3208vref / 4096.0) * (MCP3208_analogRead(i) & 0xffff)) * (div);
    }
}

uint16_t Mcp3208::MCP3208_analogRead(uint8_t pin) {
    uint16_t addr = 0b0000011000000000 |  (pin & 0b111) << 6;
    uint8_t ret[3];

    SPIReadRegister(addr,3, ret);

    return  (((ret[1] & 0x0f )<< 8)  | ret[2] );
    // return (retval);
}


void Mcp3208::update_outputs() {

}

int Mcp3208::chip_init() {

	return 0;
}


int Mcp3208::wake_driver() {
	/* Entering a reentrant critical zone.*/
	chibios_rt::CriticalSectionLocker csl;

	chSemSignalI(&mcp3208_wake);

	return 0;
}

/*==========================================================================*/
/* Driver thread.															*/
/*==========================================================================*/

static THD_FUNCTION(mcp3208_driver_thread, p) {
	int i;
	msg_t msg;

	(void)p;

	chRegSetThreadName(DRIVER_NAME);

	while (1) {
		msg = chSemWaitTimeout(&mcp3208_wake, TIME_MS2I(MCP3208_POLL_INTERVAL_MS));

		/* should we care about msg == MSG_TIMEOUT? */
		(void)msg;

		for (i = 0; i < BOARD_MCP3208_COUNT; i++) {
			auto chip = &chips[i];
			if ((chip->cfg.spi_bus == NULL) ||
				(chip->drv_state == MCP3208_DISABLED) ||
				(chip->drv_state == MCP3208_FAILED))
				continue;

        	 chip->MCP3208_read_all_chan();
		}
		lis3dh.readData();
	}
}


int Mcp3208::init() {
	int ret;
	efiPrintf("mcp3208 init called");
	ret = chip_init();
	if (ret)
		return ret;
	return 0;
}

void mcp3208_thread_start(void) {
  	chips[0].drv_state = MCP3208_READY;
  	chips[1].drv_state = MCP3208_READY;
  	chips[2].drv_state = MCP3208_READY;

	if (!drv_task_ready) {
		chThdCreateStatic(mcp3208_thread_1_wa, sizeof(mcp3208_thread_1_wa),
						  PRIO_GPIOCHIP, mcp3208_driver_thread, NULL);
		drv_task_ready = true;
	}
}


int mcp3208_add(unsigned int index) {
	int ret;
	mcp3208_config  *cfg = &(chips[index].cfg);

	if ((!cfg) || (!cfg->spi_bus) || (index >= BOARD_MCP3208_COUNT)) {
        efiPrintf("mcp3208 No cfg");
		return -1;
  }

	chips[index].o_state = 0;
	chips[index].o_state_cached = 0;
	chips[index].drv_state = MCP3208_WAIT_INIT;

	/* register, return gpio chip base */
    efiPrintf("registering chip with %d base", static_cast<int>(chips[index].cfg.cs));
	ret = gpiochip_register(Gpio::MCP3208_1_IN_1 + (index * MCP3208_ADCCH), DRIVER_NAME, chips[index], MCP3208_ADCCH);
	if (ret < 0) {
      efiPrintf("mcp3208 gpiochip_register %d", ret);
  	  return ret;
 	}

	/* set default pin names, board init code can rewrite */
	gpiochips_setPinNames(static_cast<brain_pin_e>(ret+(8*index)), mcp3208_pin_names);

    efiPrintf("mcp3208 add done = after setPinNames");
	return ret;
}

#else /* BOARD_MCP3208_COUNT > 0 */

int mcp3208_add(brain_pin_e base, unsigned int index, const mcp3208_config *cfg) {
	(void)base; (void)index; (void)cfg;

	return -1;
}


#endif /* BOARD_MCP3208_COUNT */


void mcp3208_read_0(void) {
   chips[0].mcp3208_read_0();
}

void mcp3208_read_1(void) {
    chips[0].MCP3208_read_all_chan();
    chips[1].MCP3208_read_all_chan();
    chips[2].MCP3208_read_all_chan();
}

void mcp3208_wake_driver(void) {
    efiPrintf("wake driver1");
    chips[0].wake_driver();
}

void global_init_mcp3208(void) {
    SPIDriver *spi;
	spi = getSpiDevice(config->mcp3208spidevice);
	if (spi == NULL) {
		// error already reported
		return;
	}


    if (chips[0].drv_state != MCP3208_READY && chips[0].drv_state != MCP3208_WAIT_INIT && config->mcp3208spidevice_1cs > Gpio::Unassigned) {
        chips[0].idx = 0;
    	chips[0].cfg.spi_bus = getSpiDevice(config->mcp3208spidevice);
        chips[0].cfg.cs = config->mcp3208spidevice_1cs;
        chips[0].cfg.spi_config = spicfg3208;
        initSpiCs(&chips[0].cfg.spi_config, chips[0].cfg.cs);
        mcp3208_add(0);
	    chips[0].init();
    }

    if (chips[1].drv_state != MCP3208_READY && chips[1].drv_state != MCP3208_WAIT_INIT && config->mcp3208spidevice_2cs > Gpio::Unassigned) {
        chips[1].idx = 1;
    	chips[1].cfg.spi_bus = getSpiDevice(config->mcp3208spidevice);
        chips[1].cfg.cs = config->mcp3208spidevice_2cs;
        chips[1].cfg.spi_config = spicfg3208;
        initSpiCs(&chips[1].cfg.spi_config, chips[1].cfg.cs);
        mcp3208_add(1);
	    chips[1].init();
	}

    if (chips[2].drv_state != MCP3208_READY && chips[2].drv_state != MCP3208_WAIT_INIT && config->mcp3208spidevice_3cs > Gpio::Unassigned) {
        chips[2].idx = 2;
    	chips[2].cfg.spi_bus = getSpiDevice(config->mcp3208spidevice);
        chips[2].cfg.cs = config->mcp3208spidevice_3cs;
        chips[2].cfg.spi_config = spicfg3208;
        initSpiCs(&chips[2].cfg.spi_config, chips[2].cfg.cs);
        mcp3208_add(2);
	    chips[2].init();
	}

    	efiPrintf("global mcp3208 init called");
	    efiPrintf("mcp3208 added");

            efiPrintf("init lis3dh accelerometer on same spi bus for same thread");
	init_lis3dh();

            mcp3208_thread_start();

    addConsoleAction("mcp3208_read_0", mcp3208_read_0);
    addConsoleAction("mcp3208_read_1", mcp3208_read_1);
    addConsoleAction("mcp3208_wake_driver", mcp3208_wake_driver);

}
// ---------------------------------------------------------------------

void lis3dh_t::readData(void) {
  uint8_t buf[6];
	int16_t tmp;
	if (!initialized) {
		return;
	}
    readRegister(LIS3DH_AD_STATUS, 1, buf);
    if (! (buf[0] >> 3 & 1)) { // no data available yet
    	return;
    }

	readRegister(LIS3DH_AD_OUT_X_L, 6, buf);

    tmp = (buf[0]) | (buf[1] << 8);
	engine->sensors.accelerometer.lat  =   tmp / 1000.0f;
    tmp = (buf[2]) | (buf[3] << 8);
	engine->sensors.accelerometer.lon  =   tmp / 1000.0f;
    tmp = (buf[4]) | (buf[5] << 8);
	engine->sensors.accelerometer.vert =   tmp / 1000.0f;
}


void lis3dh_t::setFreq(void) {
	if (!initialized) {
		return;
	}

    efiPrintf("LIS3DH setting frequency, scale and highres");
    uint8_t tmp = (engineConfiguration->accelerometerOrd & 0b1111 ) << 4 |
						(engineConfiguration->accelEnZ & 1) << 2 |
						(engineConfiguration->accelEnY & 1) << 1 |
						(engineConfiguration->accelEnX & 1);
	writeRegister(LIS3DH_AD_CTRL_REG1, 1, &tmp);

    // filter mode     FDS filter
	tmp =       (engineConfiguration->accelerometerHPM & 0b11)  << 6 |  // high pass mode selection
              	(engineConfiguration->accelerometerFds & 1) << 3 |      // filtered data selection
              (engineConfiguration->accelerometerHPCF & 0b11) << 4;     // filter cutoff
	writeRegister(LIS3DH_AD_CTRL_REG2, 1, &tmp);

    // set accelerometer scale, enable high resolution data , self-test
    tmp = (( engineConfiguration->accelerometerScale & 0b11 )  << 4) |      // set scale
                      (engineConfiguration->accelHighRes & 1) << 3 |       // high res
                      	(engineConfiguration->accelSelfTest & 0b11) << 1 | // self test
                      1 << 7 ;                                             // bdu
    writeRegister(LIS3DH_AD_CTRL_REG4, 1, &tmp);
}

void init_lis3dh(void) {
	SPIDriver *spi;
	spi = getSpiDevice(engineConfiguration->accelerometerSpiDevice);
	if (spi == NULL) {
		// error already reported
		return;
	}

	lis3dh.cfg.spi_bus = spi;
	lis3dh.cfg.cs = engineConfiguration->accelerometerCsPin;

	accelerometerSpiCfg.ssport = getHwPort("SPI Acc",  lis3dh.cfg.cs);
	accelerometerSpiCfg.sspad = getHwPin("SPI Acc",  lis3dh.cfg.cs);
	lis3dh.cfg.spi_config = accelerometerSpiCfg;
	lis3dh.init();
}

uint8_t lis3dh_t::whoami(void) {
    uint8_t ret;
	if (!initialized) {
		return(0);
	}

    readRegister(LIS3DH_AD_WHO_AM_I, 1, &ret);
    efiPrintf("LIS3DH: whoami  = %d ", ret);
	return ret;
}


// write one byte, register, with high bit set, signifying read
// read bytes_to_read_after_write, put them into read_buffer

void lis3dh_t::readRegister(uint8_t reg, uint8_t bytes_to_read_after_write, uint8_t *read_buffer ) {
	uint8_t cmd;
	uint8_t i;

	cmd = reg | LIS3DH_RW | LIS3DH_MS;

    initSpiCsNoOccupy(&(cfg.spi_config), cfg.cs);

	spiAcquireBus(cfg.spi_bus);
	spiStart(cfg.spi_bus, &(cfg.spi_config));
	spiSelect(cfg.spi_bus);

	spiPolledExchange(cfg.spi_bus, cmd); // write
	for (i=0;i<bytes_to_read_after_write;i++) {
		read_buffer[i] = spiPolledExchange(cfg.spi_bus, 0); // write zeroes to read length
	}

	spiUnselect(cfg.spi_bus);
	spiStop(cfg.spi_bus);
	spiReleaseBus(cfg.spi_bus);
}


// write  write_buf_size things out of the buffer, after writing the register address
void lis3dh_t::writeRegister(uint8_t reg, uint8_t write_buf_size, uint8_t *write_buffer ) {
	uint8_t cmd;
	uint8_t i;

	cmd = reg; // just write

    initSpiCsNoOccupy(&(cfg.spi_config), cfg.cs);

	spiAcquireBus(cfg.spi_bus);
	spiStart(cfg.spi_bus, &(cfg.spi_config));
	spiSelect(cfg.spi_bus);
	spiPolledExchange(cfg.spi_bus, cmd);
	for (i=0;i<write_buf_size;i++) {
		spiPolledExchange(cfg.spi_bus, write_buffer[i]);
	}

	spiUnselect(cfg.spi_bus);
	spiStop(cfg.spi_bus);
	spiReleaseBus(cfg.spi_bus);
}


void lis3dh_t::init(void) {
  initialized = true;
  whoami();
  setFreq();


}
// -------------------------------------------------------------------------------------------------------------------------

// ---------------------------------------------------------------------

//void MAX31855KASAT_t::readData(void) {
//  uint8_t buf[6];
//	int16_t tmp;
//	if (!initialized) {
//		return;
//	}
//    readRegister(LIS3DH_AD_STATUS, 1, buf);
//    if (! (buf[0] >> 3 & 1)) { // no data available yet
//    	return;
//    }
//
//	readRegister(LIS3DH_AD_OUT_X_L, 6, buf);
//
//    tmp = (buf[0]) | (buf[1] << 8);
//	engine->sensors.accelerometer.lat  =   tmp / 1000.0f;
//    tmp = (buf[2]) | (buf[3] << 8);
//	engine->sensors.accelerometer.lon  =   tmp / 1000.0f;
//    tmp = (buf[4]) | (buf[5] << 8);
//	engine->sensors.accelerometer.vert =   tmp / 1000.0f;
//}
//
//
//
//void init_MAX31855KASAT(void) {
//	SPIDriver *spi;
//    size_t i;
//
//	spi = getSpiDevice(engineConfiguration->max31855spiDevice);
//	if (spi == NULL) {
//		// error already reported
//		return;
//	}
//
//    for (i=0;i<MAX31855KASAT_COUNT;i++) {
//
//    	MAX31855KASAT[i].cfg.spi_bus = spi;
//    	MAX31855KASAT[i].cfg.cs = engineConfiguration->max31855_cs[i];
//    	egtSpiCfg.ssport = getHwPort("SPI EGT",  MAX31855KASAT[i].cfg.cs);
//    	egtSpiCfg.sspad = getHwPin("SPI EGT",  MAX31855KASAT[i].cfg.cs);
//    	MAX31855KASAT[i].cfg.spi_config = egtSpiCfg;
//    	MAX31855KASAT[i].init();
//    }
//}
//
//
//// write one byte, register, with high bit set, signifying read
//// read bytes_to_read_after_write, put them into read_buffer
//
//void MAX31855KASAT_t::readRegister(uint8_t reg, uint8_t bytes_to_read_after_write, uint8_t *read_buffer ) {
//	uint8_t cmd;
//	uint8_t i;
//
//	cmd = reg | LIS3DH_RW | LIS3DH_MS;
//
//	spiAcquireBus(cfg.spi_bus);
//	spiStart(cfg.spi_bus, &(cfg.spi_config));
//	spiSelect(cfg.spi_bus);
//	spiPolledExchange(cfg.spi_bus, cmd); // write
//	for (i=0;i<bytes_to_read_after_write;i++) {
//		read_buffer[i] = spiPolledExchange(cfg.spi_bus, 0); // write zeroes to read length
//	}
//	spiUnselect(cfg.spi_bus);
//	spiStop(cfg.spi_bus);
//	spiReleaseBus(cfg.spi_bus);
//}
//
//
//void MAX31855KASAT_t::init(void) {
//  initialized = true;
//
//
//}



#endif
