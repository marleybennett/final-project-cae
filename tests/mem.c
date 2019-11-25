#include <stdio.h>

#include "../inc/memory.h"
#include "../inc/emulator.h"

int main()
{
    struct emulator emu;
    init_emulator(&emu);

    memory_store_byte(&emu, 0x00000000, 0xFF);
    memory_store_halfword(&emu, 0x00000004, 0xFFFF);
    memory_store_word(&emu, 0x00000008, 0xFFFFFFFF);

    WORD b = memory_load_byte(&emu, 0x00000000);
    WORD hw = memory_load_halfword(&emu, 0x00000004);
    WORD w = memory_load_word(&emu, 0x00000008);

    printf("b: %x, hw: %x, w: %x\n", b, hw, w);

    deinit_emulator(&emu);
}
