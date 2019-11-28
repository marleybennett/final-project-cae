#ifndef __EXECUTE_H
#define __EXECUTE_H

#include "emulator.h"
#include "instruction.h"
#include <stdint.h>

#define FUNCT3_0 0b000
#define FUNCT3_1 0b001
#define FUNCT3_2 0b010
#define FUNCT3_3 0b011
#define FUNCT3_4 0b100
#define FUNCT3_5 0b101
#define FUNCT3_6 0b110
#define FUNCT3_7 0b111 

#define FUNCT7_0 0b0000000
#define FUNCT7_1 0b0100000

int executeInstruction(instruction ins, struct emulator * emu);


#endif
