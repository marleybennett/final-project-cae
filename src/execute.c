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

    // int test_rd;
    // int test_rs1 = 0b001101; //13
    // int test_rs2 = 0b0010001; //17
    // int test_imm = 0b0011; //3

    // test_rd = (test_rs1 ^ test_imm);
    // printf("test: %d\n", test_rd);

    if(opcode == OPCODE_I_1){
        if(funct3 == FUNCT3_0) //lb
        else if(funct3 == FUNCT3_1) //lh
        else if(funct3 == FUNCT3_2) //lw
        else if(funct3 == FUNCT3_3) //ld
        else if(funct3 == FUNCT3_4) //lbu
        else if(funct3 == FUNCT3_5) //lhu
        else if(funct3 == FUNCT3_6) //lwu

        programCounter += 1;
    }

    else if(opcode == OPCODE_I_2){
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
        
        programCounter += 1;
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
        
        programCounter += 1;
    }

    else if(opcode == OPCODE_S){
        if(funct3 == FUNCT3_0) //sb
        else if (funct3 == FUNCT3_1) //sh
        else if (funct3 == FUNCT3_2) //sw
        else if (funct3 == FUNCT3_3) //sd

        programCounter += 1;
    }

    else if(opcode == OPOCDE_R_1){
        if(funct3 == FUNCT3_0 && funct7 == FUNCT7_0) //add
            emu.registers[rd] = emu.registers[rs1] + emu.registers[rs2];
        else if(funct3 == FUNCT3_0 && funct7 == FUNCT7_1) //sub
            emu.registers[rd] = emu.registers[rs1] - emu.registers[rs2];
        else if (funct3 == FUNCT3_1 && funct7 == FUNCT7_0) //sll
            emu.registers[rd] = emu.registers[rs1] << emu.registers[rs2];
        else if (funct3 == FUNCT3_2 && funct7 == FUNCT7_0) //slt
            emu.registers[rd] = (emu.registers[rs1] < emu.registers[rs2]) ? 1:0;
        else if (funct3 == FUNCT3_3 && funct7 == FUNCT7_0) //sltu
            emu.registers[rd] = (emu.registers[rs1] < emu.registers[rs2]) ? 1:0;
        else if (funct3 == FUNCT3_4 && funct7 == FUNCT7_0) //xor
            emu.registers[rd] = (emu.registers[rs1] ^ emu.registers[rs2]);
        else if (funct3 == FUNCT3_5 && funct7 == FUNCT7_0) //srl
            emu.registers[rd] = emu.registers[rs1] >> emu.registers[rs2];
        else if (funct3 == FUNCT3_5 && funct& == FUNCT7_1) //sra
            emu.registers[rd] = emu.registers[rs1] >> emu.registers[rs2];
        else if (funct3 == FUNCT3_6 && funct& == FUNCT7_0) //or
            emu.regisers[rd] = emu.registers[rs1] | emu.registers[rs2];
        else if (funct3 == FUNCT3_7 && funct& == FUNCT7_0) //and
            emu.regisers[rd] = emu.registers[rs1] & emu.registers[rs2];

        programCounter += 1;
    }

    else if(opocde == OPCODE_U_2){
        //lui

        programCounter += 1;
    }

    else if(opcode == OPCODE_R_2){
        if(funct3 == FUNCT3_0 && funct7 = FUNCT7_0) //addw
        else if(funct3 == FUNCT3_0 && funct7 == FUNCT7_1) //subw
        else if(funct3 == FUNCT3_1 && funct7 == FUNCT7_0) //sllw
        else if(funct3 == FUNCT3_5 && funct7 == FUNCT7_0) //srlw
        else if(funct3 == FUNCT3_5 && funct7 == FUNCT7_1) //srlw

        programCounter += 1;
    }

    else if(opcode == OPCODE_SB){
        if(funct3 == FUNCT3_0) //beq
        else if(funct3 == FUNCT3_1) //bne
        else if(funct3 == FUNCT3_4) //blt
        else if(funct3 == FUNCT3_5) //bge
        else if(funct3 == FUNCT3_6) //bltu
        else if(funct3 == FUNCT3_7) //bgeu
    }

    else if(opcode == OPCODE_I_5){ //need something sorta clever here!!
        if(funct3 == FUNCT3_0) //jalr
    }

    else if(opcode == OPCODE_UJ){
        //jal
    }

    else if(opcode == OPCODE_I_4){
        if(funct3 == FUNCT3_0 && funct7 == FUNCT7_0) //ecall
        else if(funct3 == FUNCT3_0 && funct7 == FUNCT7_1) //ebreak
    }

    return programCounter;

}