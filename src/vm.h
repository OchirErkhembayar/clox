#ifndef clox_vm_h
#define clox_vm_h

#include <stdint.h>

#include "chunk.h"
#include "table.h"
#include "value.h"

#define STACK_MAX 256

typedef struct {
    Chunk* chunk; // The chunk being executed
    uint8_t* ip; // The instruction pointer. Keeps track of the next operation to be executed
    Value stack[STACK_MAX]; // The stack of values 
    Value* stack_top; // Pointer to the top of the stack
    Table globals;
    Table strings;
    Obj* objects;
} VM;

typedef enum {
    INTERPRET_OK,
    INTERPRET_COMPILE_ERROR,
    INTERPRET_RUNTIME_ERROR,
} InterpretResult;

extern VM vm;

void init_VM();
void free_VM();
void push(Value value);
Value pop();
InterpretResult interpret(const char* source);

#endif

