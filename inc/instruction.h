
#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <math.h>

#define OPCODE_R_1 51
#define OPCODE_R_2 59
#define OPCODE_S 35
#define OPCODE_I_1 3
#define OPCODE_I_2 19
#define OPCODE_I_3 27
#define OPCODE_I_4 115
#define OPCODE_U_1 23
#define OPCODE_U_2 55
#define OPCODE_UJ 111
#define OPCODE_SB 99

typedef struct{
    char opcode;
    char instructType;
    int rd; //0-31
    int rs1; //0-31
    int rs2; //0-31
    int funct3;
    int funct7;
    int immediate;
} instruction;

instruction * newInstruction(uint32_t instruction);
void freeInstruction(instruction *i);
int calculateField(uint32_t binaryInstruction, int startBit, int endBit);


void decodeRType(instruction * i, uint32_t binaryInstruction);
void decodeSType(instruction * i, uint32_t binaryInstruction);
void decodeIType(instruction * i, uint32_t binaryInstruction);
void decodeUType(instruction * i, uint32_t binaryInstruction);
void decodeUJType(instruction * i, uint32_t binaryInstruction);
void decodeSBType(instruction * i, uint32_t binaryInstruction);


#endif