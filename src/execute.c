#include "execute.h"
#include "memory.h"


int32_t signExtendImmediate(int numBits, int signBit, int32_t signedValue){
    if(signBit == 1){
        signedValue = ((0xFFFFFFFF << numBits) | signedValue); 
        printf("sign bit: 0x%0x sign extended immediate: 0x%0x\n", signBit, signedValue);
    }
    return signedValue;
}

int executeInstruction(instruction ins, struct emulator * emu){

    int programCounter = emu->program_counter;
    int opcode = ins.opcode;
    int funct3 = ins.funct3;
    int funct7 = ins.funct7;
    int unsignedImmediate= ins.immediate.u;
    int immediate = ins.immediate.s;
    int rd = ins.rd;
    int rs1 = ins.rs1;
    int rs2 = ins.rs2;
    int signBit = ins.signBit;
    int extendImmediate;
    int imm7;
    int imm5;


    if(opcode == OPCODE_I_1){
        extendImmediate = signExtendImmediate(12, signBit, immediate);

        if(funct3 == FUNCT3_0) //lb
            emu->registers[rd].s = memory_load_byte(emu, (emu->registers[rs1].s + extendImmediate));
        else if(funct3 == FUNCT3_1) //lh
            emu->registers[rd].s = memory_load_halfword(emu, (emu->registers[rs1].s + extendImmediate));
        else if(funct3 == FUNCT3_2) //lw
            emu->registers[rd].s = memory_load_word(emu, (emu->registers[rs1].s + extendImmediate));
        else if(funct3 == FUNCT3_4) //lbu
            emu->registers[rd].u = memory_load_byte(emu, (emu->registers[rs1].u + unsignedImmediate));
        else if(funct3 == FUNCT3_5) //lhu
            emu->registers[rd].u = memory_load_halfword(emu, (emu->registers[rs1].u + unsignedImmediate));
        else if(funct3 == FUNCT3_6) //lwu
            emu->registers[rd].u = memory_load_word(emu, (emu->registers[rs1].u + unsignedImmediate));

        programCounter = programCounter + 4;
    }

    else if(opcode == OPCODE_I_2){
        extendImmediate = signExtendImmediate(12, signBit, immediate);
        imm7 = (0b111111100000 & extendImmediate) >> 5;
        imm5 = (0b000000011111 & extendImmediate);  

        if(funct3 == FUNCT3_0) //addi
            emu->registers[rd].s = emu->registers[rs1].s + extendImmediate;
        else if(funct3 == FUNCT3_1 && imm7 == FUNCT7_0) //slli
            emu->registers[rd].s = emu->registers[rs1].s << imm5;
        else if(funct3 == FUNCT3_2) //slti 
            emu->registers[rd].s = (emu->registers[rs1].s < extendImmediate) ? 1:0;
        else if(funct3 == FUNCT3_3) //sltiu
            emu->registers[rd].u = (emu->registers[rs1].u < unsignedImmediate) ? 1:0; //account for unsigned??
        else if(funct3 == FUNCT3_4) //xori
            emu->registers[rd].s = emu->registers[rs1].s ^ extendImmediate;
        else if(funct3 == FUNCT3_5 && imm7 == FUNCT7_0) //srli
            emu->registers[rd].s = emu->registers[rs1].s >> imm5;
        else if(funct3 == FUNCT3_5 && imm7 == FUNCT7_1) {//srai //issues with sign extentsion
            emu->registers[rd].s = emu->registers[rs1].s >> imm5;
	}
        else if(funct3 == FUNCT3_6) //ori
            emu->registers[rd].s = emu->registers[rs1].s | extendImmediate;
        else if(funct3 == FUNCT3_7) //andi
            emu->registers[rd].s = emu->registers[rs1].s & extendImmediate;
        
        programCounter = programCounter + 4;
    }

    else if(opcode == OPCODE_U_1){ //aupic
        extendImmediate = signExtendImmediate(20, signBit, immediate);

        programCounter += (extendImmediate << 12);
    }

    else if(opcode == OPCODE_I_3){
        extendImmediate = signExtendImmediate(12, signBit, immediate);
        imm7 = (0b111111100000 & extendImmediate) >> 5;
        imm5 = (0b000000011111 & extendImmediate); 

        if(funct3 == FUNCT3_0) //addiw
            emu->registers[rd].s = emu->registers[rs1].s + extendImmediate;            
        else if(funct3 == FUNCT3_1) //slliw
            emu->registers[rd].s = emu->registers[rs1].s << extendImmediate;
        else if(funct3 == FUNCT3_5 && funct7 == FUNCT7_0) //srliw
            emu->registers[rd].s = emu->registers[rs1].s >> extendImmediate;
        else if(funct3 == FUNCT3_5 && funct7 == FUNCT7_1) //sraiw
            emu->registers[rd].s = emu->registers[rs1].s >> extendImmediate;
        
        programCounter = programCounter + 4;
    }

    else if(opcode == OPCODE_S){
        extendImmediate = signExtendImmediate(12, signBit, immediate);

        if(funct3 == FUNCT3_0) //sb
            memory_store_byte(emu, (emu->registers[rs1].s + extendImmediate), emu->registers[rs2].s);
        else if (funct3 == FUNCT3_1) //sh
            memory_store_halfword(emu, (emu->registers[rs1].s + extendImmediate), emu->registers[rs2].s);
        else if (funct3 == FUNCT3_2) //sw
            memory_store_word(emu, (emu->registers[rs1].s + extendImmediate), emu->registers[rs2].s);
        
        programCounter = programCounter + 4;
    }

    else if(opcode == OPCODE_R_1){
        if(funct3 == FUNCT3_0 && funct7 == FUNCT7_0) //add
            emu->registers[rd].s = emu->registers[rs1].s + emu->registers[rs2].s;
        else if(funct3 == FUNCT3_0 && funct7 == FUNCT7_1) //sub
            emu->registers[rd].s = emu->registers[rs1].s - emu->registers[rs2].s;
        else if (funct3 == FUNCT3_1 && funct7 == FUNCT7_0) //sll
            emu->registers[rd].s = emu->registers[rs1].s << emu->registers[rs2].s;
        else if (funct3 == FUNCT3_2 && funct7 == FUNCT7_0) //slt
            emu->registers[rd].s = (emu->registers[rs1].s < emu->registers[rs2].s) ? 1:0;
        else if (funct3 == FUNCT3_3 && funct7 == FUNCT7_0) //sltu
            emu->registers[rd].u = (emu->registers[rs1].u < emu->registers[rs2].u) ? 1:0;
        else if (funct3 == FUNCT3_4 && funct7 == FUNCT7_0) //xor
            emu->registers[rd].s = (emu->registers[rs1].s ^ emu->registers[rs2].s);
        else if (funct3 == FUNCT3_5 && funct7 == FUNCT7_0) //srl
            emu->registers[rd].s = emu->registers[rs1].s >> emu->registers[rs2].s;
        else if (funct3 == FUNCT3_5 && funct7 == FUNCT7_1) //sra
            emu->registers[rd].s = emu->registers[rs1].s >> emu->registers[rs2].s;
        else if (funct3 == FUNCT3_6 && funct7 == FUNCT7_0) //or
            emu->registers[rd].s = emu->registers[rs1].s | emu->registers[rs2].s;
        else if (funct3 == FUNCT3_7 && funct7 == FUNCT7_0) //and
            emu->registers[rd].s = emu->registers[rs1].s & emu->registers[rs2].s;

        programCounter =  programCounter + 4;
    }

    else if(opcode == OPCODE_U_2){ //lui
        extendImmediate = signExtendImmediate(20, signBit, immediate);

        emu->registers[rd].s = extendImmediate << 12;
        programCounter = programCounter + 4;
    }

    else if(opcode == OPCODE_R_2){
        if(funct3 == FUNCT3_0 && funct7 == FUNCT7_0) //addw
            emu->registers[rd].s = emu->registers[rs1].s + emu->registers[rs2].s;
        else if(funct3 == FUNCT3_0 && funct7 == FUNCT7_1) //subw
            emu->registers[rd].s = emu->registers[rs1].s - emu->registers[rs2].s;
        else if(funct3 == FUNCT3_1 && funct7 == FUNCT7_0) //sllw
            emu->registers[rd].s = emu->registers[rs1].s << emu->registers[rs2].s;
        else if(funct3 == FUNCT3_5 && funct7 == FUNCT7_0) //srlw
            emu->registers[rd].s = emu->registers[rs1].s >> emu->registers[rs2].s;
        else if(funct3 == FUNCT3_5 && funct7 == FUNCT7_1) //srlw
            emu->registers[rd].s = emu->registers[rs1].s >> emu->registers[rs2].s;

        programCounter = programCounter + 4;
    }

    else if(opcode == OPCODE_SB){
        extendImmediate = signExtendImmediate(13, signBit, immediate);

        if(funct3 == FUNCT3_0){ //beq
            if(emu->registers[rs1].s == emu->registers[rs2].s)
                programCounter = programCounter + (extendImmediate);
            else
                programCounter = programCounter + 4;
            
        }
        else if(funct3 == FUNCT3_1){ //bne
            if(emu->registers[rs1].s != emu->registers[rs2].s){
                programCounter = programCounter + extendImmediate;
            }
            else
                programCounter = programCounter + 4;
        }
        else if(funct3 == FUNCT3_4){ //blt
            if(emu->registers[rs1].s < emu->registers[rs2].s)
                programCounter = programCounter + (extendImmediate);
            else
                programCounter = programCounter + 4;
        }
        else if(funct3 == FUNCT3_5){ //bge
            if(emu->registers[rs1].s >= emu->registers[rs2].s)
                programCounter = programCounter + (extendImmediate);
            else
                programCounter = programCounter + 4;
        }
        else if(funct3 == FUNCT3_6){ //bltu
            if(emu->registers[rs1].u < emu->registers[rs2].u)
                programCounter = programCounter + (unsignedImmediate);
            else
                programCounter = programCounter + 4;
        }
        else if(funct3 == FUNCT3_7){ //bgeu
            if(emu->registers[rs1].u >= emu->registers[rs2].u)
                programCounter = programCounter + (unsignedImmediate);
            else
                programCounter = programCounter + 4;
        }
    }

    else if(opcode == OPCODE_I_5){
        extendImmediate = signExtendImmediate(12, signBit, immediate);

        if(funct3 == FUNCT3_0){ //jalr
            emu->registers[rd].s = programCounter + 4;
            programCounter = emu->registers[rs1].s + extendImmediate;
        }
    }

    else if(opcode == OPCODE_UJ){  //jal
        extendImmediate = signExtendImmediate(21, signBit, immediate);

        emu->registers[rd].s = programCounter + 4;
        programCounter = programCounter + extendImmediate;
    }

    else if(opcode == OPCODE_I_4){
        extendImmediate = signExtendImmediate(12, signBit, immediate);
        imm7 = (0b111111100000 & extendImmediate) >> 5;

        if(funct3 == FUNCT3_0 && imm7 == FUNCT7_0){ //ecall
            programCounter = -1; //end program
        }
        
    }

    return programCounter;
}
