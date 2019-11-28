#include "execute.h"
#include "memory.h"

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
    int imm7;
    int imm5;


    if(opcode == OPCODE_I_1){
        
        if(funct3 == FUNCT3_0) { //lb
            emu->registers[rd].s = memory_load_byte(emu, (emu->registers[rs1].s + immediate));
	    emu->registers[rd].s = signExtendImmediate(8, emu->registers[rd].s>>7, emu->registers[rd].s);
	}
        else if(funct3 == FUNCT3_1){ //lh
            emu->registers[rd].s = memory_load_halfword(emu, (emu->registers[rs1].s + immediate));
	    emu->registers[rd].s = signExtendImmediate(16, emu->registers[rd].s>>15, emu->registers[rd].s);
	}
        else if(funct3 == FUNCT3_2){ //lw
            emu->registers[rd].s = memory_load_word(emu, (emu->registers[rs1].s + immediate));
	}
        else if(funct3 == FUNCT3_4) //lbu
            emu->registers[rd].u = memory_load_byte(emu, (emu->registers[rs1].u + unsignedImmediate));
        else if(funct3 == FUNCT3_5) //lhu
            emu->registers[rd].u = memory_load_halfword(emu, (emu->registers[rs1].u + unsignedImmediate));
        else if(funct3 == FUNCT3_6) //lwu
            emu->registers[rd].u = memory_load_word(emu, (emu->registers[rs1].u + unsignedImmediate));

        programCounter = programCounter + 4;
    }

    else if(opcode == OPCODE_I_2){
                imm7 = (0b111111100000 & immediate) >> 5;
        imm5 = (0b000000011111 & immediate);  

        if(funct3 == FUNCT3_0) //addi
            emu->registers[rd].s = emu->registers[rs1].s + immediate;
        else if(funct3 == FUNCT3_1 && imm7 == FUNCT7_0) //slli
            emu->registers[rd].s = emu->registers[rs1].u << imm5;
        else if(funct3 == FUNCT3_2) //slti 
            emu->registers[rd].s = (emu->registers[rs1].s < immediate) ? 1:0;
        else if(funct3 == FUNCT3_3) //sltiu
            emu->registers[rd].u = (emu->registers[rs1].u < unsignedImmediate) ? 1:0; //account for unsigned??
        else if(funct3 == FUNCT3_4) //xori
            emu->registers[rd].s = emu->registers[rs1].s ^ immediate;
        else if(funct3 == FUNCT3_5 && imm7 == FUNCT7_0) //srli
            emu->registers[rd].s = emu->registers[rs1].u >> imm5;
        else if(funct3 == FUNCT3_5 && imm7 == FUNCT7_1) {//srai //issues with sign extentsion
            emu->registers[rd].s = emu->registers[rs1].s >> imm5;
	}
        else if(funct3 == FUNCT3_6) //ori
            emu->registers[rd].s = emu->registers[rs1].s | immediate;
        else if(funct3 == FUNCT3_7) //andi
            emu->registers[rd].s = emu->registers[rs1].s & immediate;
        
        programCounter = programCounter + 4;
    }

    else if(opcode == OPCODE_U_1){ //aupic
        
        emu->registers[rd].s = programCounter + immediate;//immediate;
	programCounter += 4;
    }

    else if(opcode == OPCODE_I_3){
                imm7 = (0b111111100000 & immediate) >> 5;
        imm5 = (0b000000011111 & immediate); 

        if(funct3 == FUNCT3_0) //addiw
            emu->registers[rd].s = emu->registers[rs1].s + immediate;            
        else if(funct3 == FUNCT3_1) //slliw
            emu->registers[rd].s = emu->registers[rs1].u << immediate;
        else if(funct3 == FUNCT3_5 && funct7 == FUNCT7_0) //srliw
            emu->registers[rd].s = emu->registers[rs1].u >> immediate;
        else if(funct3 == FUNCT3_5 && funct7 == FUNCT7_1) //sraiw
            emu->registers[rd].s = emu->registers[rs1].s >> immediate;
        
        programCounter = programCounter + 4;
    }

    else if(opcode == OPCODE_S){
        
        if(funct3 == FUNCT3_0) //sb
            memory_store_byte(emu, (emu->registers[rs1].s + immediate), emu->registers[rs2].s);
        else if (funct3 == FUNCT3_1) //sh
            memory_store_halfword(emu, (emu->registers[rs1].s + immediate), emu->registers[rs2].s);
        else if (funct3 == FUNCT3_2) //sw
            memory_store_word(emu, (emu->registers[rs1].s + immediate), emu->registers[rs2].s);
        
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
            emu->registers[rd].s = emu->registers[rs1].u >> emu->registers[rs2].s;
        else if (funct3 == FUNCT3_5 && funct7 == FUNCT7_1) //sra
            emu->registers[rd].s = emu->registers[rs1].s >> emu->registers[rs2].s;
        else if (funct3 == FUNCT3_6 && funct7 == FUNCT7_0) //or
            emu->registers[rd].s = emu->registers[rs1].s | emu->registers[rs2].s;
        else if (funct3 == FUNCT3_7 && funct7 == FUNCT7_0) //and
            emu->registers[rd].s = emu->registers[rs1].s & emu->registers[rs2].s;

        programCounter =  programCounter + 4;
    }

    else if(opcode == OPCODE_U_2){ //lui
        
        emu->registers[rd].s = immediate;//immediate;
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
        
        if(funct3 == FUNCT3_0){ //beq
            if(emu->registers[rs1].s == emu->registers[rs2].s)
                programCounter = programCounter + (immediate);
            else
                programCounter = programCounter + 4;
            
        }
        else if(funct3 == FUNCT3_1){ //bne
            if(emu->registers[rs1].s != emu->registers[rs2].s){
                programCounter = programCounter + immediate;
            }
            else
                programCounter = programCounter + 4;
        }
        else if(funct3 == FUNCT3_4){ //blt
            if(emu->registers[rs1].s < emu->registers[rs2].s)
                programCounter = programCounter + (immediate);
            else
                programCounter = programCounter + 4;
        }
        else if(funct3 == FUNCT3_5){ //bge
            if(emu->registers[rs1].s >= emu->registers[rs2].s)
                programCounter = programCounter + (immediate);
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
        
        if(funct3 == FUNCT3_0){ //jalr
            emu->registers[rd].s = programCounter + 4;
            programCounter = emu->registers[rs1].s + immediate;
        }
    }

    else if(opcode == OPCODE_UJ){  //jal
        
        emu->registers[rd].s = programCounter + 4;
        programCounter = programCounter + immediate;
    }

    else if(opcode == OPCODE_I_4){
	imm7 = (0b111111100000 & immediate) >> 5;

        if(funct3 == FUNCT3_0 && imm7 == FUNCT7_0){ //ecall
	    if (emu->registers[10].u == 10)
	    {
		programCounter = -1; //end program
	    }
	    else {
		programCounter += 4;
	    }
        }
        
    }

    return programCounter;
}
