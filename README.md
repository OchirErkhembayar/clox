# Notes

## Source -> **COMPILER** -> Bytecode -> **VIRTUAL MACHINE** -> execution

## Basic operation of this interpreter
1. Initialise a chunk
2. Each write to the chunk requires the op_code and line number
3. We can also add constants to a chunk.
   - Add the OP_CONSTANT op_code to the chunk
   - Add the constant to the value array
   - The function returns the index of the constant
   - Store the index of the constant in the byte code array
   - When we encounter an OP_CONSTANT instruction we know the next index holds
     a reference to the constant in the constant pool

## Chapter 14
### Chunks of bytecode

#### Bytecode
- Simpler "version of machine code"
- Run by an enulator, a *virtual machine*

- Each bytecode has a 1 byte **operation code** eg. add, subtract, return etc.
-

#### Chunk *Not sure if this is an official term*
##### Contents
###### OpCodes
- An array of op codes which are unsigned integers
- Each one corresponds to an instruction

###### Constant pools
- An array of pointers to values stored on the heap
- We use the term **ValueArray** and it is a property of the Chunk

###### Lines
- We keep track of the line number of the source code of a byte by having
  another array side by side of the codes which contains the number

