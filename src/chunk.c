#include <stdlib.h>

#include "chunk.h"
#include "memory.h"
#include "value.h"

/* Initialising chunk
 * ------------------
 *  We start off completely empty
 */
void init_chunk(Chunk* chunk) {
    chunk->count = 0;
    chunk->capacity = 0;
    chunk->code = NULL; // This is best practise for initialising pointers if there is no value
    chunk->lines = NULL;
    init_value_array(&chunk->constants);
}

// Here we are adding a byte to the chunk
void write_chunk(Chunk* chunk, uint8_t byte, int line) {
    if (chunk->capacity < chunk->count + 1) {
        int old_capacity = chunk->capacity;
        chunk->capacity = GROW_CAPACITY(old_capacity);
        chunk->code = GROW_ARRAY(uint8_t, chunk->code, old_capacity, chunk->capacity);
        chunk->lines = GROW_ARRAY(int, chunk->lines, old_capacity, chunk->capacity);
    }

    chunk->code[chunk->count] = byte;
    chunk->lines[chunk->count] = line;
    chunk->count++;
}

void free_chunk(Chunk* chunk) {
    // Deallocate the memory
    FREE_ARRAY(uint8_t, chunk->code, chunk->capacity);
    FREE_ARRAY(uint8_t, chunk->lines, chunk->capacity);
    free_value_array(&chunk->constants);
    // We then zero out the chunk
    init_chunk(chunk);
}

int add_constant(Chunk* chunk, Value value) {
    // Add the value to the constant pool
    write_value_array(&chunk->constants, value);
    // We then return the index of the value
    return chunk->constants.count - 1;
}

