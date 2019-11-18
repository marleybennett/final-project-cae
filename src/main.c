#include <stdio.h>
#include "emulator.h"
#include "instruction.h"

int main(int argc, char *argv[])
{
    struct emulator emu;

    printf("Loading program: %s\n", argv[1]);

    load_program(&emu, argv[1]);

    printf("Program length is %d\n", emu.program.instruction_count);

    instruction *ins;
    for (int i = 0; i < emu.program.instruction_count; ++i)
    {
	printf("%x: %08x\n", i, emu.program.instructions[i]);
	ins = newInstruction(emu.program.instructions[i]);
	freeInstruction(ins);
	printf("-------------------------------\n\n");
    }

    return 0;
}
