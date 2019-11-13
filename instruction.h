
#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <math.h>


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