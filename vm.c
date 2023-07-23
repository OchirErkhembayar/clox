#include <stdint.h>
#include <stdio.h>

#include "common.h"
#include "debug.h"
#include "value.h"
#include "vm.h"

VM vm;

static void reset_stack() {
    vm.stack_top = vm.stack;
}

void init_VM() {
    reset_stack();
}

void free_VM() {
}

/* The stack points to the next available spot at the top
 * So since the spot that it points to is free:
 * 1. Set the value at that spot
 * 2. Increment the pointer up one (luckily this isn't ASM so we don't need to add bytes lol)
 */
void push(Value value) {
    *vm.stack_top = value; // Store value at the array elem at the top of the stack
    vm.stack_top++; // Stack top should point at the next AVAILABLE spot so we increment to the next one
}

Value pop() {
    vm.stack_top--; // Decrement so it points to the value at the top
    return *vm.stack_top; // Return that value
}

static InterpretResult run() {
    // Get the next value and then increment the instruction pointer
    #define READ_CONSTANT() (vm.chunk->constants.values[READ_BYTE()])
    #define READ_BYTE() (*vm.ip++) // ++ returns the current value THEN increments
    #define BINARY_OP(op) \
        do { \
            double b = pop(); \
            double a = pop(); \
            push(a op b); \
        } while (false) // Little trick because we need a ";" after a do while loop

    for (;;) {
        #ifdef DEBUG_TRACE_EXECUTION
            printf("           ");
            for (Value* slot = vm.stack; slot < vm.stack_top; slot++) {
                printf("[");
                print_value(*slot);
                printf("]");
            }
            printf("\n");
            disassemble_instruction(vm.chunk, (int)(vm.ip - vm.chunk->code));
        #endif

        uint8_t instruction;
        switch (instruction = READ_BYTE()) {
            case OP_CONSTANT: {
                Value constant = READ_CONSTANT();
                push(constant);
                break;
            }
            case OP_ADD: BINARY_OP(+); break;
            case OP_SUBTRACT: BINARY_OP(-); break;
            case OP_MULTIPLY: BINARY_OP(*); break;
            case OP_DIVIDE: BINARY_OP(/); break;
            case OP_NEGATE: {
                *(vm.stack_top - sizeof(Value) / 8) *= -1;
                break;
            };
            case OP_RETURN: {
                print_value(pop()); // Debugging hax
                printf("\n");
                return INTERPRET_OK;
                break;
            }
        }
    }

    #undef READ_BYTE
    #undef READ_CONSTANT
    #undef BINARY_OP
}

InterpretResult interpret(Chunk *chunk) {
    vm.chunk = chunk;
    vm.ip = vm.chunk->code;

    return run();
}

