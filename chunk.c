#include <stdlib.h>

#include "chunk.h"
#include "memory.h"

/* Initialising chunk
 * ------------------
 *  We start off completely empty
 */
void init_chunk(Chunk* chunk) {
    chunk->count = 0;
    chunk->capacity = 0;
    chunk->code = NULL; // This is best practise for initialising pointers if there is no value
}

void write_chunk(Chunk* chunk, uint8_t byte) {
    if (chunk->capacity < chunk->count + 1) {
        int old_capacity = chunk->capacity;
        chunk->capacity = GROW_CAPACITY(old_capacity);
        chunk->code = GROW_ARRAY(uint8_t, chunk->code, old_capcity, chunk->capacity);
    }

    chunk->code[chunk->count] = byte;
    chunk->count++;
}
