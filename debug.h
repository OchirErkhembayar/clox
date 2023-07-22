#ifndef clox_debug_h
#define clox_debug_h

#include "chunk.h"

/*
 * disassemble_chunk disassembles an entire chunk and uses
 * disassemble_instruction to disassemble each instruction.
 */
void disassemble_chunk(Chunk* chunk, const char* name);
int disassemble_instruction(Chunk* chunk, int offset);

#endif
