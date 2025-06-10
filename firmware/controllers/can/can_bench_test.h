/**
 * file can_bench_test.h
 */

#pragma once
#include "can.h"

void processCanQcBenchTest(const CANRxFrame& frame);
void sendQcBenchEventCounters();
void sendQcBenchButtonCounters();
void sendQcBenchAuxDigitalCounters();
void sendQcBenchRawAnalogValues();
void sendQcBenchBoardStatus();
void initQcBenchControls();
void handleButtonBox(uint16_t index);
uint16_t hwButtonBox1Lookup(uint16_t index);