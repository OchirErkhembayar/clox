#include "common.h"
#include "chunk.h"
#include "debug.h"
#include "vm.h"

int main() {
    // Set the stack pointer the the top of the stack (very beginning)
    init_VM();
    
    // Initialise the chunk and its constant pool (set array counts to zero and NULL pointers)
    Chunk chunk;
    init_chunk(&chunk);

    int constant;
    // Add a constant to value array of the chunk
    // Add the constant op code to chunk
    // Add the index of that const next so the VM can find it
    constant = add_constant(&chunk, 3);
    write_chunk(&chunk, OP_CONSTANT, 123);
    write_chunk(&chunk, constant, 123);
    
    constant = add_constant(&chunk, 6);
    write_chunk(&chunk, OP_CONSTANT, 123);
    write_chunk(&chunk, constant, 123);

    write_chunk(&chunk, OP_ADD, 123);

    constant = add_constant(&chunk, 3);
    write_chunk(&chunk, OP_CONSTANT, 123);
    write_chunk(&chunk, constant, 123);

    write_chunk(&chunk, OP_DIVIDE, 123);
    
    constant = add_constant(&chunk, 10.5);
    write_chunk(&chunk, OP_CONSTANT, 123);
    write_chunk(&chunk, constant, 123);

    write_chunk(&chunk, OP_MULTIPLY, 123);

    write_chunk(&chunk, OP_NEGATE, 123);

    write_chunk(&chunk, OP_RETURN, 123);

    disassemble_chunk(&chunk, "test chunk");

    interpret(&chunk);

    // Free memory
    free_VM();
    free_chunk(&chunk);
    
    return 0;
}
