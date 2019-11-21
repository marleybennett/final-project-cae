#include "execute.h"

int executeInstruction(instruction ins, struct emulator * emu){

    int programCounter = emu->program_counter;
    int opcode = ins.opcode;
    int funct3 = ins.funct3;
    int funct7 = ins.funct7; //or immediate?
    int immediate = ins.immediate.s;
    int unsignedImmediate= ins.immediate.u;
    int rd = ins.rd;
    int rs1 = ins.rs1;
    int rs2 = ins.rs2;

    int test_rd;
    int test_rs1 = 0b001101; //13
    int test_rs2 = 0b0010001; //17
    int test_imm = 0b0011; //3

    test_rd = (test_rs1 ^ test_imm);
    printf("test: %d\n", test_rd);

    if(opcode == OPCODE_I_1){
        if(funct3 == FUNCT3_0) //lb
            emu->registers[rd] = memory_load_byte(emu, (emu->registers[rs1].s + immediate));
        else if(funct3 == FUNCT3_1) //lh
            emu->registers[rd] = memory_load_halfword(emu, (emu->registers[rs1].s + immediate));
        else if(funct3 == FUNCT3_2) //lw
            emu->registers[rd] = memory_load_word(emu, (emu->registers[rs1].s + immediate));
        else if(funct3 == FUNCT3_4) //lbu
            emu->registers[rd] = memory_load_byte(emu, (emu->registers[rs1].u + immediate));
        else if(funct3 == FUNCT3_5) //lhu
            emu->registers[rd] = memory_load_halfword(emu, (emu->registers[rs1].u + immediate));
        else if(funct3 == FUNCT3_6) //lwu
            emu->registers[rd] = memory_load_word(emu, (emu->registers[rs1].u + immediate));

        programCounter = programCounter 1;
    }

    else if(opcode == OPCODE_I_2){
        if(funct3 == FUNCT3_0) //addi
            emu->registers[rd] = emu->registers[rs1].s + immediate;
        else if(funct3 == FUNCT3_1 && funct7 == FUNCT7_0) //slli
            emu->registers[rd] = emu->registers[rs1].s << immediate;
        else if(funct3 == FUNCT3_2) //slti 
            emu->registers[rd] = (emu->registers[rs1].s < immediate) ? 1:0;
        else if(funct3 == FUNCT3_3) //sltiu
            emu->registers[rd] = (emu->registers[rs1].s < unsignedImmediate) ? 1:0; //acconunt for unsigned??
        else if(funct3 == FUNCT3_4) //xori
            emu->registers[rd] = emu->registers[rs1].s ^ immediate;
        else if(funct3 == FUNCT3_5 && funct7 == FUNCT7_0) //srli
            emu->registers[rd] = emu->registers[rs1].s >> immediate;
        else if(funct3 == FUNCT3_5 && funct7 == FUNCT7_1) //srai
            emu->registers[rd] = emu->registers[rs1].s >> immediate;
        else if(funct3 == FUNCT3_6) //ori
            emu->registers[rd] = emu->registers[rs1].s | immediate;
        else if(funct3 == FUNCT3_7) //andi
            emu->registers[rd] = emu->registers[rs1].s & immediate;
        
        programCounter = programCounter 1;
    }

    else if(opcode == OPCODE_U_1){ //aupic
        programCounter += (immediate << 12);
    }

    else if(opcode == OPOCDE_I_3){
        if(funct3 == FUNCT3_0) //addiw
            emu->registers[rd] = emu->registers[rs1].s + immediate;            
        else if(funct3 == FUNCT3_1) //slliw
            emu->registers[rd] = emu->registers[rs1].s << immediate;
        else if(funct3 == FUNCT3_5 && funct7 == FUNCT7_0) //srliw
            emu->registers[rd] = emu->registers[rs1].s >> immediate;
        else if(funct3 == FUNCT3_5 && funct7 == FUNCT7_1) //sraiw
            emu->registers[rd] = emu->registers[rs1].s >> immediate;
        
        programCounter = programCounter 1;
    }

    else if(opcode == OPCODE_S){
        if(funct3 == FUNCT3_0) //sb
            memory_store_byte(emu, (emu->registers[rs1].s + immediate), emu->registers[rs2].s);
        else if (funct3 == FUNCT3_1) //sh
            memory_store_halfword(emu, (emu->registers[rs1].s + immediate), emu->registers[rs2].s);
        else if (funct3 == FUNCT3_2) //sw
            memory_store_word(emu, (emu->registers[rs1].s + immediate), emu->registers[rs2].s);
        
        programCounter = programCounter 1;
    }

    else if(opcode == OPOCDE_R_1){
        if(funct3 == FUNCT3_0 && funct7 == FUNCT7_0) //add
            emu->registers[rd] = emu->registers[rs1].s + emu->registers[rs2].s;
        else if(funct3 == FUNCT3_0 && funct7 == FUNCT7_1) //sub
            emu->registers[rd] = emu->registers[rs1].s - emu->registers[rs2].s;
        else if (funct3 == FUNCT3_1 && funct7 == FUNCT7_0) //sll
            emu->registers[rd] = emu->registers[rs1].s << emu->registers[rs2].s;
        else if (funct3 == FUNCT3_2 && funct7 == FUNCT7_0) //slt
            emu->registers[rd] = (emu->registers[rs1].s < emu->registers[rs2].s) ? 1:0;
        else if (funct3 == FUNCT3_3 && funct7 == FUNCT7_0) //sltu
            emu->registers[rd] = (emu->registers[rs1].u < emu->registers[rs2].u) ? 1:0;
        else if (funct3 == FUNCT3_4 && funct7 == FUNCT7_0) //xor
            emu->registers[rd] = (emu->registers[rs1].s ^ emu->registers[rs2].s);
        else if (funct3 == FUNCT3_5 && funct7 == FUNCT7_0) //srl
            emu->registers[rd] = emu->registers[rs1].s >> emu->registers[rs2].s;
        else if (funct3 == FUNCT3_5 && funct& == FUNCT7_1) //sra
            emu->registers[rd] = emu->registers[rs1].s >> emu->registers[rs2].s;
        else if (funct3 == FUNCT3_6 && funct& == FUNCT7_0) //or
            emu->regisers[rd] = emu->registers[rs1].s | emu->registers[rs2].s;
        else if (funct3 == FUNCT3_7 && funct& == FUNCT7_0) //and
            emu->regisers[rd] = emu->registers[rs1].s & emu->registers[rs2].s;

        programCounter = programCounter 1;
    }

    else if(opocde == OPCODE_U_2){
        emu->registers[rd] = immediate;
        programCounter += 1;
    }

    else if(opcode == OPCODE_R_2){
        if(funct3 == FUNCT3_0 && funct7 = FUNCT7_0) //addw
        else if(funct3 == FUNCT3_0 && funct7 == FUNCT7_1) //subw
        else if(funct3 == FUNCT3_1 && funct7 == FUNCT7_0) //sllw
        else if(funct3 == FUNCT3_5 && funct7 == FUNCT7_0) //srlw
        else if(funct3 == FUNCT3_5 && funct7 == FUNCT7_1) //srlw

        programCounter = programCounter 1;
    }

    else if(opcode == OPCODE_SB){
        if(funct3 == FUNCT3_0){ //beq
            if(emu->registers[rs1].s == emu->registers[rs2].s)
                programCounter = programCounter + (immediate << 1);
            else
                programCounter = programCounter 1;
            
        }
        else if(funct3 == FUNCT3_1){ //bne
            if(emu->registers[rs1].s != emu->registers[rs2].s)
                programCounter = programCounter + (immediate << 1);
            else
                programCounter = programCounter 1;
        }
        else if(funct3 == FUNCT3_4){ //blt
            if(emu->registers[rs1].s < emu->registers[rs2].s)
                programCounter = programCounter + (immediate << 1);
            else
                programCounter = programCounter 1;
        }
        else if(funct3 == FUNCT3_5){ //bge
            if(emu->registers[rs1].s >= emu->registers[rs2].s)
                programCounter = programCounter + (immediate << 1);
            else
                programCounter = programCounter 1;
        }
        else if(funct3 == FUNCT3_6){ //bltu
            if(emu->registers[rs1].u < emu->registers[rs2].u)
                programCounter = programCounter + (unsignedImmediate << 1);
            else
                programCounter = programCounter 1;
        }
        else if(funct3 == FUNCT3_7){ //bgeu
            if(emu->registers[rs1].u >= emu->registers[rs2].u)
                programCounter = programCounter + (unsignedImmediate << 1);
            else
                programCounter = programCounter 1;
        }
    }

    else if(opcode == OPCODE_I_5){
        if(funct3 == FUNCT3_0){ //jalr
            emu->registers[rd] = programCounter + 1;
            programCounter = emu->registers[rs1].s + immediate;
        }
    }

    else if(opcode == OPCODE_UJ){  //jal
        emu->registers[rd] = programCounter + 1;
        programCounter = programCounter + (immediate << 1);
    }

    else if(opcode == OPCODE_I_4){
        if(funct3 == FUNCT3_0 && funct7 == FUNCT7_0){ //ecall
            programCounter = -1; //end program
        }
        
    }

    return programCounter;

}