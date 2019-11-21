#ifndef __EMULATOR_H
#define __EMULATOR_H

#include <stdint.h>

#define WORD_LENGTH_BITS (32)
#define WORD_LENGTH_BYTES (WORD_LENGTH_BITS/8)

typedef uint32_t WORD;
typedef uint8_t BYTE;

typedef union {
    uint32_t u;
    int32_t s;
} usint32_t;

struct program {
    WORD instruction_count;
    WORD *instructions;
};

struct emulator {
    usint32_t registers[32];
    WORD program_counter;
    struct program program;
    BYTE *memory;
};

int load_program(struct emulator *emu, char *filename);
int init_emulator(struct emulator *emu);
void deinit_emulator(struct emulator *emu);

#endif
