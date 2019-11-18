#ifndef __EMULATOR_H
#define __EMULATOR_H

#include <stdint.h>

#define WORD_LENGTH_BITS (32)
#define WORD_LENGTH_BYTES (WORD_LENGTH_BITS/8)

typedef uint32_t WORD;

struct program {
    WORD instruction_count;
    WORD *instructions;
};

struct emulator {
    WORD registers[32];
    WORD program_counter;
    struct program program;
};

int load_program(struct emulator *emu, char *filename);

#endif
