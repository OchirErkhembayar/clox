# Notes

## Source -> **COMPILER** -> Bytecode -> **VIRTUAL MACHINE** -> execution

## Chapter 14
### Chunks of bytecode

#### Bytecode
- Simpler "version of machine code"
- Run by an enulator, a *virtual machine*

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


## Chapter 15
### A Virtual Machine

#### VM
- Executes the bytecode, essentially acting as a CPU
- Basically runs through the codes stored in a chunk and executes them

##### The stack
- When we're executing an expression we need to keep track of some temporary variables
- print (1 + 3) + add(3, 5);
- The expression must
- 1. Calculate (1 + 3), store that somewhere
  2. Calculate add(3, 5) (which is a bunch of stuff happening too), store that somewhere
  3. Then it needs to add those two stored values together and pass it to print
- In the Tree Walk Intepreter we just stored them in variables
- This time we'll store them on an array, pushing and popping off it as we need to
- That's the stack

So basically when we reach an instruction which says **OP_CONST** we will be pushing whatever value
comes after that on to the stack

##### Basic arithmetic example
**1 + 3 / 2**

###### Bytecode instructions
1. Initialise a VM
2. Initialise a chunk
3. Add 1 to the constant pool
4. Add an OP_CONST bytecode to the codes
5. Add the index of 1 in the constant pool to the codes
6. Add 3 to the constant pool
7. Add an OP_CONST bytecode to the codes
8. Add the index of 3 in the constant pool to the codes
9. Add the OP_ADD bytecode to the codes
10. Add 4 to the constant pool
11. Add the OP_CONST bytecode to the codes
12. Add the index of 4 to the codes
13. Add the OP_DIVIDE bytecode to the codes

###### What is happening
1. - Initialise the stack pointer (point it to the top of the empty stack)
2. - Set capacity, count to 0
   - Initialise the value array (constant pool)
     - Set the capacity, count to 0
     - Initialise the value pointer to NULL
3. Append 1 to the value array of the chunk and get its index
4. Append OP_CONST to the codes in the chunk (the VM will load the following value into the stack)
5. Add the index of one to the codes so that the VM knows how to get it
6. Repeat
7. Repeat
8. Repeat
9. The VM will pop a value off the stack (3), then again (1) add them together and push that onto the stack
10. Repeat
11. Repeat
12. Repeat
13. The VM will pop a value off the stack (2), then again (4) and then divide 4 by 2 and push that onto the stack

Now the stack has 4 at the top, ready to be stored in a variable or printed or maybe it's just part of a larger expression **(1 + 3 / 2) + 5**
