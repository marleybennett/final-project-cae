#include <stdio.h>

#include "../inc/emulator.h"

int main()
{
    struct emulator emu;
    init_emulator(&emu);

    for (int i = 0; i < 32; ++i)
    {
	emu.registers[i].u = 1<<i;
    }

    output_registers(&emu, "pows_of_two.bin");

    for (int i = 0; i < 32; ++i)
    {
	emu.registers[i].u = (1<<i)-1;
    }

    // "Mersenne numbers" as in 2^n - 1, not Mersenne primes
    output_registers(&emu, "mersenne.bin");

    for (int i = 0; i < 32; ++i)
    {
	emu.registers[i].s = -1 * ((1<<i) - 1);
    }

    output_registers(&emu, "neg_mersenne.bin");

    deinit_emulator(&emu);
}
