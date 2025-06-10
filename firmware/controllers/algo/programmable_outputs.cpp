/* programmable_outputs.cpp


 */

#include "pch.h"
#include "programmable_outputs.h"
#include "board_id.h"
#include "tunerstudio.h"

uint32_t prevprint = 0;

void  updateProgrammableOutputs(void) {
	size_t portNum = 0;
	updateTunerStudioState();

	for (portNum = 0;portNum < PROGPORTS; portNum++) {
			setProgrammableOutput(portNum);
	}
}


void registerProgrammablePort(size_t portNum) {
#if EFI_PROD_CODE
	if (getBoardId() > 0) { // custom board with an id
		if (getBoardMetaOutputsCount() > (int) portNum) {
			auto outputs = getBoardMetaOutputs();
			auto gpio_brain_pin =  outputs[portNum];
			int brain_pin = (int) outputs[portNum];
			efiPrintf("CUSTOM PROGPIN outputsCount: %d, portNum: %d => brain_pin: %d, brain_pin_index: %d", getBoardMetaOutputsCount(), portNum, brain_pin, brainPin_to_index(gpio_brain_pin) );

			if (getBrainUsedPin(brainPin_to_index(gpio_brain_pin))) {
					if (prevprint != engine->outputChannels.seconds) {
						efiPrintf("ERROR: pin %d is used by %s", brain_pin, getBrainUsedPin(brainPin_to_index(gpio_brain_pin)));
						prevprint = engine->outputChannels.seconds;
					}
				return;
			}
			enginePins.progPorts[portNum].initPin("PROGPORT", gpio_brain_pin);
			enginePins.progPorts[portNum].setValue(nullptr, engineConfiguration->portsPowerOnValue[portNum], 0 ); // set power on value
			engine->outputChannels.progPortOutput[portNum] = 0;
			bitset(engine->outputChannels.progPortOutput[portNum], 7); // mark our pin inited
		} else {
			efiPrintf("portNum > getBoardMetaOutputsCount(), maybe offboard ? ");
		}

	} else { // generic board with an MCU and ports, all, or some in
#endif
		auto brain_pin = static_cast<brain_pin_e>(portNum + 2);

		if (getBrainUsedPin(brainPin_to_index(brain_pin))) {

			if (prevprint != engine->outputChannels.seconds ) {
				efiPrintf("ERROR: pin %d is used by %s", (int) brain_pin, getBrainUsedPin(brainPin_to_index(brain_pin)));
				prevprint = engine->outputChannels.seconds;
			}
			return;
		}
		enginePins.progPorts[portNum].initPin("PROGPORT", static_cast<brain_pin_e>(brain_pin)); // GREASY
		enginePins.progPorts[portNum].setValue(nullptr, engineConfiguration->portsPowerOnValue[portNum], 0 ); // set power on value
		engine->outputChannels.progPortOutput[portNum] = 0;
		bitset(engine->outputChannels.progPortOutput[portNum], 7); // mark our pin as inited
#if EFI_PROD_CODE
	}
#endif

}

void unregisterProgrammablePort(size_t portNum) {
	efiPrintf("unregister PROGPORT %d ", portNum);
	if (!bitcheck(engine->outputChannels.progPortOutput[portNum], 7)) {
		efiPrintf("unregister called on port not marked as registered with progports - this shouldn't happen");
		// port did not get registerd, means conflict, do nothing
		return;
	}

#if EFI_PROD_CODE
	if (getBoardId() > 0) {
		efiPrintf("custom board de-init");
		if (getBoardMetaOutputsCount() > (int) portNum) { // don't do something dumb
			enginePins.progPorts[portNum].deInit(engineConfiguration->portsPowerOnValue[portNum]);
			engine->outputChannels.progPortOutput[portNum] = 0;
		}

	} else {
#endif
#if EFI_PROD_CODE
		enginePins.progPorts[portNum].deInit(engineConfiguration->portsPowerOnValue[portNum]);
		engine->outputChannels.progPortOutput[portNum] = 0;
	}
#endif


}


void setProgrammableOutput(size_t portNum) {
	size_t condNum=0;

	bool portCond = false;

	// port is enabled,
	if (engineConfiguration->portsEnabled[portNum] > 0) {
		// check if we registered PROGPORT , 8th bit is that
		if (!bitcheck(engine->outputChannels.progPortOutput[portNum], 7)) { // port is not registered
			registerProgrammablePort(portNum);               // register
		}

		if (!bitcheck(engine->outputChannels.progPortOutput[portNum], 7)) { // port is not registered - above failed
			// port did not get registerd, means conflict, do nothing
			return;
		}

		// get first condition, always active if port enabled
		portCond = getProgrammableOutputCond(portNum, condNum);

		// step through portsConnectors , which is  conditions - 1
		for (condNum=1;condNum<PROGPORTS_CONDITIONS; condNum++) {
			if (engineConfiguration->portsConnector[condNum-1][portNum] == '&') {
				portCond = portCond && getProgrammableOutputCond(portNum, condNum);
			} else if (engineConfiguration->portsConnector[condNum-1][portNum] == '|') {
				portCond = portCond || getProgrammableOutputCond(portNum, condNum);
			} else {
				break;
			}
		}

		if (bitcheck(engine->outputChannels.progPortOutput[portNum], 0) != portCond) {
			efiPrintf("cond changed %d state now %d", portNum, portCond);
			if (portCond) {
				bitset(engine->outputChannels.progPortOutput[portNum], 0);
				enginePins.progPorts[portNum].setValue(nullptr, engineConfiguration->portsTriggerValue[portNum], 0 ); // set poweron value
			} else {
				enginePins.progPorts[portNum].setValue(nullptr, engineConfiguration->portsPowerOnValue[portNum], 0 ); // set poweron value
				bitclear(engine->outputChannels.progPortOutput[portNum], 0);
			}

		}
	} else { // port is  disabled check if registered
		if (bitcheck(engine->outputChannels.progPortOutput[portNum], 7)) { // port is registered
			unregisterProgrammablePort(portNum);                // unregister
			bitclear(engine->outputChannels.progPortOutput[portNum], 7);
		}
	}
}


bool  getProgrammableOutputCond(size_t portNum, size_t condNum) {
	bool portCond = 0;
	uint8_t size = 0;
	uint8_t realsize = 0;
	uint8_t is_signed = 0;
	uint8_t is_float = 0;

	uint16_t offset=0;
	int16_t threshold = 0;
	int16_t hysteresis = 0;

	int32_t value = 0;
	uint32_t uvalue = 0;
	float fvalue = 0;


	uint8_t outpcb[4] = { 0, 0, 0, 0 } ;
	void *ptr1;
	char *ptr2;
	char cond = 0;

	if (engineConfiguration->portsEnabled[portNum] == 0) {
		return engineConfiguration->portsPowerOnValue[portNum];
	}

	if (engineConfiguration->portsEnabled[portNum] > 0) {
		offset =     engineConfiguration->portsReadOffset[condNum][portNum];
		size =       engineConfiguration->portsSize      [condNum][portNum];
		threshold  = engineConfiguration->portsThreshold [condNum][portNum];
		cond       = engineConfiguration->portsCondition [condNum][portNum];
		hysteresis = engineConfiguration->portsHysteresis[condNum][portNum];

		realsize = size & 0x0f;
		is_signed = !((size & 0x80) > 0); // jank in the docs.
		is_float = (size & 0x40) > 0;

		ptr1 = &engine->outputChannels;
		ptr2 = (char *) ptr1;
		ptr2+=offset;
		if (realsize <= 4) {
			memcpy(outpcb,ptr2, realsize);
		}

		if (realsize == 1) {
			uvalue = outpcb[0] & 0xff;
		} else if (realsize == 2) {
		   uvalue = (outpcb[0] & 0xff) +
				   ((outpcb[1] & 0xff) << 8);
		} else if (realsize == 4) {
		   uvalue = (outpcb[0] & 0xff)          +
			   	   ((outpcb[1] & 0xff) << 8)    +
			   	   ((outpcb[2] & 0xff) << 16)   +
			   	   ((outpcb[3] & 0xff) << 24);
		}

		switch (cond) {
			case '=':
				if (is_signed == 1 && is_float == 0) {
					value = uvalue;
					if (value == threshold) {
						portCond = 1;
					}
					break;
				}

				if (is_signed == 0 && is_float == 0) {
					if (uvalue == (uint32_t) threshold) {
						portCond = 1;
					}
					break;
				}

				if (is_float == 1) {
					fvalue = uvalue;
					if (fvalue == threshold) {
						portCond = 1;
					}
					break;
				}

			break;
			case '>':
				if (is_signed == 1 && is_float == 0) {
					value = uvalue;
					if (bitcheck(engine->outputChannels.progPortOutput[portNum], 1 + condNum)) {
						value += hysteresis;
					}
					if (value > threshold) {
						portCond = 1;
					}
					break;
				}

				if (is_signed == 0 && is_float == 0) {
					if (bitcheck(engine->outputChannels.progPortOutput[portNum], 1 + condNum)) {
						uvalue += hysteresis;
					}

					if (uvalue > (uint32_t)threshold) {
						portCond = 1;
					}
					break;
				}

				if (is_float == 1) {
					fvalue = uvalue;
					if (bitcheck(engine->outputChannels.progPortOutput[portNum], 1 + condNum)) {
						fvalue += hysteresis;
					}

					if (fvalue > threshold) {
						portCond = 1;
					}
					break;
				}
				break;

			case '<':
				if (is_signed == 1 && is_float == 0) {
					value = uvalue;
					if (bitcheck(engine->outputChannels.progPortOutput[portNum], 1 + condNum)) {
						value -= hysteresis;
					}
					if (value < threshold) {
						portCond = 1;
					}
					break;
				}

				if (is_signed == 0 && is_float == 0) {
					if (bitcheck(engine->outputChannels.progPortOutput[portNum], 1 + condNum)) {
						if ( uvalue > (uint32_t)hysteresis ) { // check we're above 0 with hysteresis
							uvalue -= hysteresis;
						} else {
							uvalue = 0;
						}
					}
					if (uvalue < (uint32_t)threshold) {
						portCond = 1;
					}
					break;
				}

				if (is_float == 1) {
					fvalue = uvalue;
					if (bitcheck(engine->outputChannels.progPortOutput[portNum], 1 + condNum)) {
						fvalue -= hysteresis;
					}
					if (fvalue < threshold) {
						portCond = 1;
					}
					break;
				}

			break;

			case '&': // AND  should probably do something here for negatives, i.e. engine
				if ((uvalue & threshold) > 0 )  {
					portCond = 1;
				}
			break;


			case '!': // NOT equal to
				if (is_signed == 1 && is_float == 0) {
					value = uvalue;
					if (value != threshold) {
						portCond = 1;
					}
					break;
				}

			if (is_signed == 0 && is_float == 0) {
				if (uvalue != (uint32_t) threshold) {
					portCond = 1;
				}
				break;
			}

			if (is_float == 1) {
				fvalue = uvalue;
				if (fvalue != threshold) {
					portCond = 1;
				}
				break;
			}
			break;


		}

/*		if (prevprint != engine->outputChannels.seconds && condNum > 0) {
			efiPrintf("cn=%d, offs=%d, cond=%c, sz=%d, rsiz=%d, is_s=%d,  is_f=%d, uval=%ld, val=%ld, fv=%f, thresh=%d, pCond=%d, psc1=%d, pdc2=%d",
					   condNum, offset,  cond,    size,  realsize,is_signed,is_float,uvalue,   value,   fvalue,threshold, portCond, engineConfiguration->portsConnector[0][portNum], engineConfiguration->portsConnector[1][portNum]);

			prevprint = engine->outputChannels.seconds;

		}*/

	}



	if (portCond == 1) {
		bitset(engine->outputChannels.progPortOutput[portNum], 1 + condNum);
	} else if (portCond == 0) {
		bitclear(engine->outputChannels.progPortOutput[portNum], 1 + condNum);
	}
	return portCond;

}
