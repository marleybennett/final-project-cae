#include <stdio.h>
#include "execute.h"
#include "emulator.h"
#include "instruction.h"

int main(int argc, char *argv[])
{
    struct emulator emu;

    printf("Loading program: %s\n", argv[1]);

    load_program(&emu, argv[1]);

    printf("Program length is %d\n", emu.program.instruction_count);

    // instruction ins;
    // for (int i = 0; i < emu.program.instruction_count; ++i)
    // {
	// printf("%x: %08x\n", i, emu.program.instructions[i]);
	// ins = newInstruction(emu.program.instructions[i]);
	// printf("-------------------------------\n\n");
    // }

    instruction ins;
    emu.program_counter = 0;

    emu.registers[0].s = 0;

    while((emu.program_counter != -1) && (emu.program_counter < (emu.program.instruction_count - 1))){
	    printf("program counter: %d; %08x\n", emu.program_counter, emu.program.instructions[emu.program_counter]);
	    ins = newInstruction(emu.program.instructions[emu.program_counter]);
        emu.program_counter = executeInstruction(ins, &emu);
        for(int i = 0; i < 3; i++)
            printf("\t %d: %0x\n", i+10, emu.registers[i+10].s);
        printf("-------------------------------\n\n");
        
    }

    printf("----\nregister content:\n ");

    for(int i = 0; i < 32; i++){
        printf("%d: %0x\n", i, emu.registers[i].s);
    }

    return 0;
}
