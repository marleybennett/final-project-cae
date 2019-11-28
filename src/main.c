#include <stdio.h>
#include "execute.h"
#include "emulator.h"
#include "instruction.h"

// The attribute allows us to overwrite the main function without the
// compiler complaining about multiple definitions of the
// function. This makes testing easier and requires no Makefile
// shenanigans. 
__attribute__((weak)) int main(int argc, char *argv[])
{
    if (argc < 2)
    {
	printf("Usage:\n%s filename\n", argv[0]);
    }

    struct emulator emu;
    
    int err = 0;
    char *filename = argv[1];

    err = init_emulator(&emu);
    if (err != 0)
    {
	printf("Failed to initialize emulator\n");
	goto out;
    }
    
    printf("Loading program: %s\n", filename);
    err = load_program(&emu, filename);
    if (err != 0)
    {
	printf("Failed to load file %s\n", filename);
	goto out;

    }

    instruction ins;

    while(emu.program_counter>>2 < emu.program.instruction_count)
    {
	emu.registers[0].s = 0;
	ins = newInstruction(emu.program.instructions[emu.program_counter>>2]);
        emu.program_counter = executeInstruction(ins, &emu);
    }

    printf("Register file contents:\n ");

    for(int i = 0; i < 32; i++){
        printf("%d: %0x\n", i, emu.registers[i].s);
    }
    output_registers(&emu, "registers.bin");


out:
    deinit_emulator(&emu);
    return err;
}
