#include "instruction.h"

instruction newInstruction(WORD binaryCode){

    instruction instruct;

    instruct.opcode = calculateField(binaryCode, 0, 6);
    printf("opcode: %d\n", instruct.opcode);

    /* Identify opcode (in decimal) and corresponding instruction type */
    if(instruct.opcode == OPCODE_R_1 || instruct.opcode == OPCODE_R_2){
        instruct.instructType = 'R';
        instruct = decodeRType(instruct, binaryCode);
    }

    else if(instruct.opcode == OPCODE_S){
        instruct.instructType = 'S';
        instruct = decodeSType(instruct, binaryCode);
    }

    else if(instruct.opcode == OPCODE_I_1 || instruct.opcode == OPCODE_I_2 || instruct.opcode == OPCODE_I_3 || instruct.opcode == OPCODE_I_4){
        instruct.instructType = 'I';
        instruct = decodeIType(instruct, binaryCode);
    }

    else if(instruct.opcode == OPCODE_U_1 || instruct.opcode ==  OPCODE_U_2){
        instruct.instructType = 'U';
        instruct = decodeUType(instruct, binaryCode);
    }

    else if(instruct.opcode == OPCODE_UJ){
        instruct.instructType = 'J'; //Type UJ
        instruct = decodeUJType(instruct, binaryCode);
    }

    else if(instruct.opcode == OPCODE_SB){
        instruct.instructType = 'B'; //Type SB
        instruct = decodeSBType(instruct, binaryCode);
    }
    else
    {
        fprintf(stderr, "Invalid opcode.\n");
    }
    

    printf("instruction Type: %c\n",  instruct.instructType);
  
    return instruct;
}

/*
    Use bitwise operator AND to remove the unnecessary higher bits.
    Shift result to eliminate the uneccesary lower bits.
    Return only the bits in the desired range.
*/
int calculateField(WORD binaryInstruction, int startBit, int endBit){
    
    uint32_t totalBits = (1<<(endBit+1)) - 1;
    int value = ((totalBits & binaryInstruction) >> startBit);
    return value;
}

instruction decodeRType(instruction i, WORD binaryInstruction){
    
    i.rd = calculateField(binaryInstruction, 7, 11);
    i.funct3 = calculateField(binaryInstruction, 12, 14);
    i.rs1 = calculateField(binaryInstruction, 15, 19);
    i.rs2 = calculateField(binaryInstruction, 20, 24);
    i.funct7 = calculateField(binaryInstruction, 25, 31);

    printf("rd: 0x%x\n", i.rd);
    printf("funct3: 0x%x\n", i.funct3);
    printf("rs1: 0x%x\n", i.rs1);
    printf("rs2: 0x%x\n", i.rs2);
    printf("funct7: 0x%x\n", i.funct7);  

    return i; 
}

instruction decodeIType(instruction i, WORD binaryInstruction){

    i.rd = calculateField(binaryInstruction, 7, 11);
    i.funct3 = calculateField(binaryInstruction, 12, 14);
    i.rs1 = calculateField(binaryInstruction, 15, 19);
    i.immediate = calculateField(binaryInstruction, 20, 24);


    printf("destination register: 0x%x\n", i.rd);
    printf("funct3: 0x%x\n", i.funct3);
    printf("rs1: 0x%x\n", i.rs1);
    printf("immediate: 0x%x\n", i.immediate);
 
    return i;
}


instruction decodeSType(instruction i, WORD binaryInstruction){

    i.immediate = calculateField(binaryInstruction, 7, 11);
    i.immediate += (calculateField(binaryInstruction, 20, 31) << 5);
    
    i.funct3 = calculateField(binaryInstruction, 12, 14);
    i.rs1 = calculateField(binaryInstruction, 15, 19);
    i.rs2 = calculateField(binaryInstruction, 20, 24);

    printf("funct3: 0x%x\n", i.funct3);
    printf("rs1: 0x%x\n", i.rs1);
    printf("rs2: 0x%x\n", i.rs2);
    printf("immediate: 0x%x\n", i.immediate);   

    return i;
}

instruction decodeSBType(instruction i, WORD binaryInstruction){

    i.immediate = (calculateField(binaryInstruction, 8, 11) << 1);
    i.immediate += (calculateField(binaryInstruction, 25, 30) << 5);
    i.immediate += (calculateField(binaryInstruction, 7, 7) << 11);
    i.immediate += (calculateField(binaryInstruction, 31, 31) << 12);

    i.funct3 = calculateField(binaryInstruction, 12, 14);
    i.rs1 = calculateField(binaryInstruction, 15, 19);
    i.rs2 = calculateField(binaryInstruction, 20, 24);

    printf("funct3: 0x%x\n", i.funct3);
    printf("rs1: 0x%x\n", i.rs1);
    printf("rs2: 0x%x\n", i.rs2);
    printf("immediate: 0x%x\n", i.immediate);   
    
    return i;
}

instruction decodeUType(instruction i, WORD binaryInstruction){

    i.rd = calculateField(binaryInstruction, 7, 11);
    i.immediate = calculateField(binaryInstruction, 12, 31);

    printf("rd: 0x%x\n", i.rd);   
    printf("immediate: 0x%x\n", i.immediate);   

    return i;
}

instruction decodeUJType(instruction i, WORD binaryInstruction){
    
    i.rd = calculateField(binaryInstruction, 7, 11);

    i.immediate = (calculateField(binaryInstruction, 12, 19) << 12);
    i.immediate += (calculateField(binaryInstruction, 20, 20) << 11);
    i.immediate += (calculateField(binaryInstruction, 21, 30) << 1);
    i.immediate += (calculateField(binaryInstruction, 31, 31) << 20);

    printf("rd: 0x%x\n", i.rd);   
    printf("immediate: 0x%x\n", i.immediate);  

    return i;
}

//  int main() { 
//      uint32_t sampleRInstruction = 2595154355; 
//      uint32_t sampleSInstruction = 1533848995; 
//      uint32_t sampleSBInstruction = 2897955555; 
//      uint32_t sampleUJInstruction = 1775678959; 
//      uint32_t sampleIInstruction = 766424723; 
//     // printf("sample instruction: %" PRId8 "\n", sampleRInstruction); */
   
//      instruction instruct = newInstruction(sampleIInstruction); 
//      freeInstruction(instruct);
//  } 
