
#ifndef __INSTRUCTION_H
#define __INSTRUCTION_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <math.h>


#define OPCODE_R_1 0b110011
#define OPCODE_R_2 0b111011
#define OPCODE_S 0b100011
#define OPCODE_I_1 0b11
#define OPCODE_I_2 0b10011
#define OPCODE_I_3 0b11011
#define OPCODE_I_4 0b1110011
#define OPCODE_U_1 0b10111
#define OPCODE_U_2 0b110111
#define OPCODE_UJ 0b1101111
#define OPCODE_SB 0b1100011

#define TEST 0b11011

typedef uint32_t WORD;

typedef struct{
    int opcode;
    char instructType;
    int rd; //0-31
    int rs1; //0-31
    int rs2; //0-31
    int funct3;
    int funct7;
    usint32_t immediate;
} instruction;

instruction newInstruction(WORD instruction);
int calculateField(WORD binaryInstruction, int startBit, int endBit);


instruction decodeRType(instruction i, WORD binaryInstruction);
instruction decodeSType(instruction i, WORD binaryInstruction);
instruction decodeIType(instruction i, WORD binaryInstruction);
instruction decodeUType(instruction i, WORD binaryInstruction);
instruction decodeUJType(instruction i, WORD binaryInstruction);
instruction decodeSBType(instruction i, WORD binaryInstruction);


#endif
