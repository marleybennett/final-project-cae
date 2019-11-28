#include "memory.h"
#include "emulator.h"

void memory_store_word(struct emulator *emu, WORD addr, WORD data)
{
    memory_store_halfword(emu, addr, data);
    memory_store_halfword(emu, addr+2, data>>16);
}

void memory_store_halfword(struct emulator *emu, WORD addr, WORD data)
{
    memory_store_byte(emu, addr, data);
    memory_store_byte(emu, addr + 1, data >> 8);
}

void memory_store_byte(struct emulator *emu, WORD addr, WORD data)
{
    emu->memory[addr] = data & 0xFF;
}

WORD memory_load_word(struct emulator *emu, WORD addr)
{
    WORD value = memory_load_halfword(emu, addr+2) << 16;
    value |= memory_load_halfword(emu, addr);
    return value;
}

WORD memory_load_halfword(struct emulator *emu, WORD addr)
{
    WORD value = memory_load_byte(emu, addr+1) << 8;
    value |= memory_load_byte(emu, addr);
    return value;
}

WORD memory_load_byte(struct emulator *emu, WORD addr)
{
    return emu->memory[addr] & 0xFF;
}
