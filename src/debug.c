#include <stdio.h>

#include "debug.h"

void disassemble_chunk(Chunk* chunk, const char* name) {
    printf("== %s ==\n", name);

    // Iterate over the chunk's instructions
    for (int offset = 0; offset < chunk->count;) {
        // Print the offset of the instruction
        offset = disassemble_instruction(chunk, offset);
    }
}

static int simple_instruction(const char* name, int offset) {
    printf("%s\n", name);
    return offset + 1;
}

static int constant_instruction(const char* name, Chunk* chunk, int offset) {
    // We go + 1 because the first byte is the opcode, next byte is the index of the constant
    uint8_t constant = chunk->code[offset + 1];
    // We print the name and the value of the constant
    printf("%-16s %4d '", name, constant);
    print_value(chunk->constants.values[constant]);
    printf("'\n");
    // Constant instructions are two bytes long
    return offset + 2;
}

int disassemble_instruction(Chunk* chunk, int offset) {
    // Print the offset of the instruction
    printf("%04d ", offset);
    if (offset > 0 && chunk->lines[offset] == chunk->lines[offset - 1]) {
        // If the same line as the previous instruction, print a vertical bar
        printf("   | ");
    } else {
        printf("%4d ", chunk->lines[offset]);
    }

    // Print the instruction's opcode
    uint8_t instruction = chunk->code[offset];
    switch (instruction) {
        case OP_RETURN:
            return simple_instruction("OP_RETURN", offset);
        case OP_NEGATE:
            return simple_instruction("OP_NEGATE", offset);
        case OP_CONSTANT:
            return constant_instruction("OP_CONSTANT", chunk, offset);
        case OP_NIL:
            return simple_instruction("OP_NIL", offset);
        case OP_TRUE:
            return simple_instruction("OP_TRUE", offset);
        case OP_FALSE:
            return simple_instruction("OP_FALSE", offset);
        case OP_EQUAL:
            return simple_instruction("OP EQUAL", offset);
        case OP_GREATER:
            return simple_instruction("OP_GREATER", offset);
        case OP_LESS:
            return simple_instruction("OP LESS", offset);
        case OP_ADD:
            return simple_instruction("OP_ADD", offset);
        case OP_SUBTRACT:
            return simple_instruction("OP_SUBTRACT", offset);
        case OP_MULTIPLY:
            return simple_instruction("OP_MULTIPLY", offset);
        case OP_DIVIDE:
            return simple_instruction("OP_DIVIDE", offset);
        case OP_NOT: 
            return simple_instruction("OP_NOT", offset);
        default:
            printf("Unknown opcode %d\n", instruction);
            return offset + 1;
    }
}

