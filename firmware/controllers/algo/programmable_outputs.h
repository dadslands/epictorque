#pragma once


bool getProgrammableOutputCond(size_t portNum, size_t condNum);
void setProgrammableOutput(size_t portNum);
void  updateProgrammableOutputs(void);
void registerProgrammablePort(size_t portNum);
void unregisterProgrammablePort(size_t portNum);

