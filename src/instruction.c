#include "instruction.h"

instruction * newInstruction(uint32_t binaryCode){

    instruction * instruct =  malloc(sizeof(*instruct));
    if(instruct == NULL){
        fprintf(stderr, "Memory allocation error.\n");
        return NULL;
    }

    instruct->opcode = calculateField(binaryCode, 0, 6);
    printf("opcode: %x\n", instruct->opcode);

    /* Identify opcode (in decimal) and corresponding instruction type */
    if(instruct->opcode == OPCODE_R_1 || instruct->opcode == OPCODE_R_2){
        instruct->instructType = 'R';
        decodeRType(instruct, binaryCode);
    }

    else if(instruct->opcode == OPCODE_S){
        instruct->instructType = 'S';
        decodeSType(instruct, binaryCode);
    }

    else if(instruct->opcode == OPCODE_I_1 || instruct->opcode == OPCODE_I_2 || instruct->opcode == OPCODE_I_3 || instruct->opcode == OPCODE_I_4){
        instruct->instructType = 'I';
        decodeIType(instruct, binaryCode);
    }

    else if(instruct->opcode == OPCODE_U_1 || instruct->opcode ==  OPCODE_U_2){
        instruct->instructType = 'U';
        decodeUType(instruct, binaryCode);
    }

    else if(instruct->opcode == OPCODE_UJ){
        instruct->instructType = 'J'; //Type UJ
        decodeUJType(instruct, binaryCode);
    }

    else if(instruct->opcode == OPCODE_SB){
        instruct->instructType = 'B'; //Type SB
        decodeSBType(instruct, binaryCode);
    }
    else
    {
        fprintf(stderr, "Invalid opcode.\n");
        return NULL;
    }
    

    printf("instruction Type: %c\n",  instruct->instructType);
    return instruct;
}

void freeInstruction(instruction * i){
    free(i);
}


/*
    Use bitwise operator AND to remove the unnecessary higher bits.
    Shift result to eliminate the uneccesary lower bits.
    Return only the bits in the desired range.
*/
int calculateField(uint32_t binaryInstruction, int startBit, int endBit){
    
    uint32_t totalBits = (1<<(endBit+1)) - 1;
    int value = ((totalBits & binaryInstruction) >> startBit);
    return value;
}

void decodeRType(instruction * i, uint32_t binaryInstruction){
    
    i->rd = calculateField(binaryInstruction, 7, 11);
    i->funct3 = calculateField(binaryInstruction, 12, 14);
    i->rs1 = calculateField(binaryInstruction, 15, 19);
    i->rs2 = calculateField(binaryInstruction, 20, 24);
    i->funct7 = calculateField(binaryInstruction, 25, 31);

    printf("rd: 0x%x\n", i->rd);
    printf("funct3: 0x%x\n", i->funct3);
    printf("rs1: 0x%x\n", i->rs1);
    printf("rs2: 0x%x\n", i->rs2);
    printf("funct7: 0x%x\n", i->funct7);   
}

void decodeIType(instruction * i, uint32_t binaryInstruction){

    i->rd = calculateField(binaryInstruction, 7, 11);
    i->funct3 = calculateField(binaryInstruction, 12, 14);
    i->rs1 = calculateField(binaryInstruction, 15, 19);
    i->immediate = calculateField(binaryInstruction, 20, 24);


    printf("destination register: 0x%x\n", i->rd);
    printf("funct3: 0x%x\n", i->funct3);
    printf("rs1: 0x%x\n", i->rs1);
    printf("immediate: 0x%x\n", i->immediate);
 
}


void decodeSType(instruction * i, uint32_t binaryInstruction){

    i->immediate = calculateField(binaryInstruction, 7, 11);
    i->immediate += (calculateField(binaryInstruction, 20, 31) << 5);
    
    i->funct3 = calculateField(binaryInstruction, 12, 14);
    i->rs1 = calculateField(binaryInstruction, 15, 19);
    i->rs2 = calculateField(binaryInstruction, 20, 24);

    printf("funct3: 0x%x\n", i->funct3);
    printf("rs1: 0x%x\n", i->rs1);
    printf("rs2: 0x%x\n", i->rs2);
    printf("immediate: 0x%x\n", i->immediate);   

}

void decodeSBType(instruction * i, uint32_t binaryInstruction){

    i->immediate = (calculateField(binaryInstruction, 8, 11) << 1);
    i->immediate += (calculateField(binaryInstruction, 25, 30) << 5);
    i->immediate += (calculateField(binaryInstruction, 7, 7) << 11);
    i->immediate += (calculateField(binaryInstruction, 31, 31) << 12);

    i->funct3 = calculateField(binaryInstruction, 12, 14);
    i->rs1 = calculateField(binaryInstruction, 15, 19);
    i->rs2 = calculateField(binaryInstruction, 20, 24);

    printf("funct3: 0x%x\n", i->funct3);
    printf("rs1: 0x%x\n", i->rs1);
    printf("rs2: 0x%x\n", i->rs2);
    printf("immediate: 0x%x\n", i->immediate);   

}

void decodeUType(instruction * i, uint32_t binaryInstruction){

    i->rd = calculateField(binaryInstruction, 7, 11);
    i->immediate = calculateField(binaryInstruction, 12, 31);

    printf("rd: 0x%x\n", i->rd);   
    printf("immediate: 0x%x\n", i->immediate);   


}

void decodeUJType(instruction * i, uint32_t binaryInstruction){
    
    i->rd = calculateField(binaryInstruction, 7, 11);

    i->immediate = (calculateField(binaryInstruction, 12, 19) << 12);
    i->immediate += (calculateField(binaryInstruction, 20, 20) << 11);
    i->immediate += (calculateField(binaryInstruction, 21, 30) << 1);
    i->immediate += (calculateField(binaryInstruction, 31, 31) << 20);

    printf("rd: 0x%x\n", i->rd);   
    printf("immediate: 0x%x\n", i->immediate);   

}

/* int main() { */
/*     uint32_t sampleRInstruction = 2595154355; */
/*     uint32_t sampleSInstruction = 1533848995; */
/*     uint32_t sampleSBInstruction = 2897955555; */
/*     uint32_t sampleUJInstruction = 1775678959; */
/*     uint32_t sampleIInstruction = 766424723; */

/*     // printf("sample instruction: %" PRId8 "\n", sampleRInstruction); */
    
/*     instruction* instruct = newInstruction(sampleIInstruction); */
/*     freeInstruction(instruct); */
/* } */
