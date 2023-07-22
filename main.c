#include "common.h"
#include "chunk.h"
#include "debug.h"

int main() {
    Chunk chunk;
    init_chunk(&chunk);

    // Add a constant to chunk
    int constant = add_constant(&chunk, 1.2);
    // Add the bytecode to chunk
    write_chunk(&chunk, OP_CONSTANT, 123);
    // Add the index of the constant to chunk
    write_chunk(&chunk, constant, 123);

    write_chunk(&chunk, OP_RETURN, 123);

    disassemble_chunk(&chunk, "test chunk");
    free_chunk(&chunk);

    return 0;
}
