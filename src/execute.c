#include "execute.h"

int executeInstruction(instruction ins, struct emulator emu){

    int programCounter = emu.program_counter;
    int opcode = ins.opcode;
    int funct3 = ins.funct3;
    int funct7 = ins.funct7; //or immediate?
    int immediate = ins.immediate;
    int rd = ins.rd;
    int rs1 = ins.rs1;
    int rs2 = ins.rs2;

    //skipping all loads :D

    // int test_rd;
    // int test_rs1 = 0b001101; //13
    // int test_rs2 = 0b0010001; //17
    // int test_imm = 0b0011; //3

    // test_rd = (test_rs1 ^ test_imm);
    // printf("test: %d\n", test_rd);

    if(opcode == OPCODE_I_2){
        if(funct3 = FUNCT3_0) //addi
            emu.registers[rd] = emu.registers[rs1] + immediate;
        else if(funct3 == FUNCT3_1 && funct7 == FUNCT7_0) //slli
            emu.registers[rd] = emu.registers[rs1] << immediate;
        else if(funct3 = FUNCT3_2) //slti 
            emu.registers[rd] = (emu.registers[rs1] < immediate) ? 1:0; //account for signed??
        else if(funct3 = FUNCT3_3) //sltiu
            emu.registers[rd] = (emu.registers[rs1] < immediate) ? 1:0; //acconunt for unsigned??
        else if(funct3 == FUNCT3_4) //xori
            emu.registers[rd] = emu.registers[rs1] ^ immediate;
        else if(funct3 == FUNCT3_5 && funct7 == FUNCT7_0) //srli
            emu.registers[rd] = emu.registers[rs1] >> immediate;
        else if(funct3 == FUNCT3_5 && funct7 == FUNCT7_1) //srai
            emu.registers[rd] = emu.registers[rs1] >> immediate;
        else if(funct3 == FUNCT3_6) //ori
            emu.registers[rd] = emu.registers[rs1] | immediate;
        else if(funct3 == FUNCT3_7) //andi
            emu.registers[rd] = emu.registers[rs1] & immediate;
        
        programCounter+=1;
    }

    else if(opcode == OPCODE_U_1){ //aupic
        programCounter += immediate;
    }

    else if(opcode == OPOCDE_I_3){
        if(funct3 == FUNCT3_0) //addiw -- account for word??
            emu.registers[rd] = emu.registers[rs1] + immediate;            
        else if(funct3 == FUNCT3_1) //slliw -- account for word??
            emu.registers[rd] = emu.registers[rs1] << immediate;
        else if(funct3 == FUNCT3_5 && funct7 == FUNCT7_0) //srliw
            emu.registers[rd] = emu.registers[rs1] >> immediate;
        else if(funct3 == FUNCT3_5 && funct7 == FUNCT7_1) //sraiw
            emu.registers[rd] = emu.registers[rs1] >> immediate;
    }

    return programCounter;

}