#include <stdio.h>
#include "emulator.h"

int main(int argc, char *argv[])
{
    struct emulator emu;

    printf("Loading program: %s\n", argv[1]);

    load_program(&emu, argv[1]);

    printf("Program length is %d\n", emu.program.instruction_count);

    for (int i = 0; i < emu.program.instruction_count; ++i)
    {
	printf("%x: %08x\n", i, emu.program.instructions[i]);
    }

    return 0;
}
