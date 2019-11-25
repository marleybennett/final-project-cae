#include <stdio.h>
#include <stdlib.h>
#include "emulator.h"

int init_emulator(struct emulator *emu)
{
    emu->program_counter = 0;
    emu->memory = malloc(0x200000);
    if (emu->memory == NULL)
    {
	return -1;
    }

    return 0;
}

void deinit_emulator(struct emulator *emu)
{
    free(emu->memory);
}

int load_program(struct emulator *emu, char *filename)
{
    if (emu == NULL || filename == NULL)
    {
	return -1;
    }

    FILE *f;
    long file_len;
    char *file_contents;

    f = fopen(filename, "rb");
    if (f == NULL)
    {
	return -1;
    }

    fseek(f, 0, SEEK_END);
    file_len = ftell(f);
    rewind(f);

    file_contents = malloc(file_len);

    // Loop over words
    for (int word_idx = 0; word_idx < file_len/WORD_LENGTH_BYTES; ++word_idx)
    {
	printf("Reading word %d\n", word_idx);
	// Loop over each byte in word, inserting into program in
	// reverse order. The instructions are in Little Endian and
	// our encoding is done assuming Big Endian.
        for (int byte_idx = WORD_LENGTH_BYTES - 1; byte_idx >= 0; --byte_idx)
	{
	    int idx = WORD_LENGTH_BYTES * (word_idx+1) - byte_idx - 1;
	    printf("Writing word %d, byte %d to file_contents[%d]\n",
		   word_idx, byte_idx, idx);
	    fread(&file_contents[idx], sizeof(char), 1, f);
        }
    }
    
    emu->program.instructions = (WORD *)file_contents;
    emu->program.instruction_count = file_len / WORD_LENGTH_BYTES;

    fclose(f);
    return 0;
}
