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
    emu.program_counter = 1;

    while(1){
	    printf("%08x\n", emu.program.instructions[emu.program_counter]);
	    ins = newInstruction(emu.program.instructions[emu.program_counter]);
        emu.program_counter = executeInstruction(ins, emu);
        printf("-------------------------------\n\n");
        if(emu.program_counter > emu.program.instruction_count)
            break;
    }

    return 0;
}
