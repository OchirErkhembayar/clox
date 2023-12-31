/*
 * C - Note
 * --------
 *  typedef is used to create an alias name for another data type.
 *  here we are creating an alias for uint8_t as OpCode.
 *  So, we can use OpCode instead of uint8_t.
 *
 *  So if we do something like this:
 *  typedef uint8_t OpCode;
 *  then we can use OpCode instead of uint8_t.
 *  OpCode code = 5;
 *
 *  In this case we're using enums
 *  enum in C is basically a set of integer constants.
 *
 *  If we didn't use typedef then it would look like this
 *  enum OpCode {
 *    OP_RETURN,
 *  };
 *
 *  enum OpCode code = OP_RETURN;
 *
 *  with typedef we can do this
 *  OpCode code = OP_RETURN;
 */

#ifndef clox_chunk_h
#define clox_chunk_h

#include "common.h"
#include "value.h"

/* Clox - Note
 * -----------
 * OpCode
 * ------
 * In our bytecode format, each instruction has a 1 byte opcode
 * That number controls what type of operation we're performing.
 * We are defining the opcodes here.
 *
 * Chunk
 * -----
 * Bytecode is a series of instructions stored one after another.
 * We need to store the bytecode instruction code somewhere.
 * Since we don't know the length of the bytecode, we can't use a fixed size array.
 * So we use a dynamic array.
 *
 * We keep track of
 * 1. The number of elements in the array.
 * 2. The capacity of the array.
 * 3. The array itself.
 * 4. The line number of the instruction.
 * 5. The constant table. // see value.h
 */

typedef enum {
    OP_CONSTANT, // Add a value to the stack
    OP_NIL,
    OP_TRUE,
    OP_FALSE,
    OP_POP,
    OP_GET_GLOBAL,
    OP_DEFINE_GLOBAL,
    OP_SET_GLOBAL,
    OP_EQUAL,
    OP_GREATER,
    OP_LESS,
    OP_ADD,
    OP_SUBTRACT,
    OP_MULTIPLY,
    OP_DIVIDE,
    OP_NOT,
    OP_NEGATE, // Unary negation
    OP_PRINT,
    OP_RETURN,
} OpCode;

typedef struct {
    int count; // The number of elements in the array.
    int capacity; // The number of elements the array can hold before it needs to grow.
    uint8_t* code; // The bytecode array (the opcodes)
    int* lines; // Array of line numbers for each instruction
    ValueArray constants; // The constant table
} Chunk;

void init_chunk(Chunk* chunk);
void free_chunk(Chunk* chunk);
void write_chunk(Chunk* chunk, uint8_t byte, int line);
int add_constant(Chunk* chunk, Value value);

#endif
