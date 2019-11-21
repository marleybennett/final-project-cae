#ifndef __MEMORY_H
#define __MEMORY_H

#include <stdint.h>
#include "emulator.h"

void memory_store_word(struct emulator *emu, WORD addr, WORD data);
void memory_store_halfword(struct emulator *emu, WORD addr, WORD data);
void memory_store_byte(struct emulator *emu, WORD addr, WORD data);

WORD memory_load_word(struct emulator *emu, WORD addr);
WORD memory_load_halfword(struct emulator *emu, WORD addr);
WORD memory_load_byte(struct emulator *emu, WORD addr);

#endif
