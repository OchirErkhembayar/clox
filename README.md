# Notes

## Source -> **SCANNER** -> Tokens -> **COMPILER** -> Bytecode chunk -> **VIRTUAL MACHINE** -> execution


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

## Chapter 16
### Scanning on demand

#### Reading source code
- We can either operate in a REPL or read source code and execute it
- We'll now need a new scanner to generate tokens for the compiler to turn into chunks of bytecode

##### Reading files
- We just use C's standard library functions to allocate a block of memory for the user's program and store the source code there

##### Scanning
- This time we shouldn't scan the entire file in one go.
- This would be really inefficient because we'll have to have some sort of dynamic array to keep track of everything
- Also it's not necessary because we only need to see 1 token ahead

##### One token at a time
- The simplest solutio is to only scan a token when the compiler needs one
- Then we just scan a single token, pass it to the compiler and wait for it to ask for another
- This way we don't have to dynamically allocate anything or pass by reference
- We define a struct Token which has a type, where in the source string it starts and its length
- TokenType enum tells us what type of token it is
- We have a large switch statement to get the TokenType

##### Keywords and 
- In order to efficiently find out what keyword we need we use a **deterministic finite automaton (DFA)**
- This is also known a a **state machine**
- We basically look at whether or not the first character of the next token matches the first characters
  of any of our keywords
- If it does then we check what keywords it could be based on that letter and continue until we either
  have a keyword or not
- If we don't then that means it was an identifier

## Chapter 17
### Compiling expressions

#### Top-down operator precedence parsing

#### Infix expressions
- Infix expressions are those where we don't know what type of expressions we're in until we're in the middle of it
- For example in **1 + 3** we don't know that we're in a binary expression until after we have parsed the **1**

#### Operation (executing a single expression)

##### This is how a simple expression like **1 + 3** is executed

##### 1. Initialisation
- Open the file and measure its length and get a buffer to that file
- Initialise a **chunk** to store the bytecodes
- Compile the source code into bytes

##### 2. Compilation
- Initialise the scanner
- Advance once, consume the first token
  The parser's current token is now the first token and second is still uninitialised
- Our default precedence is set to **PREC_ASSIGNMENT**
- Advance again, consume the second token
  The parser's current token is now **+** and the previous is **1**
- Check the ParseFn associated with the previous token (1)
- This token must have a prefix function or else we've got something like 33
  as two tokens instead of 1 token which makes no sense
- Now we execute the prefix function **number()**
- The number function will cast the previous token into a **double** and call **emit_constant**
- This will call **emit_bytes** which will call **emite_byte** twice o
  The first one the **OP_CONST** op-code
  And then create a new **Value** to hold the **double** and add it to the **value_array** of the chunk
  then emit the index of the new value as a byte
- **emit_byte** essentially creates a new **OP_CODE** which is just a **uint8_t** and adds it to the **codes**
  of the **chunk**. It is either an **OP_CODE** or an **operand** which is an index of the **value_array*
- Now the compiler will get a new rule by getting from the rules table using the index of the current token 
  and compare the precedence of that one against the current one
  - If the precedence is greater than or equal to the first rule then we can continue
  - Otherwise we will stop.
- We will continue because the current token is **+** which has a higher precedence level than an **PREC_ASSIGNMENT**
- Now we will advance. Setting the current token to **3** and the previous to **+**
- Now we will call the **infix()** of the rule corresponding to **+** which is **binary()**
- We will get the rule for the binary operator
- We will now call **parse_precedence** again with the precedence of **+** rule which is **PREC_TERM** + 1 (for left-associativity)
- This will make us advance once so that we're currently at **TOKEN_EOF** and previous is **3**
- Again, the prefix rule of this is **number** so we will call that, adding **OP_CONST** and the index of **3** onto the chunk
- Because **TOKEN_NUMBER** has **PREC_NONE** which is lower than **PREC_TERM + 1** we will stop and go back to **binary**
- Now we just do a switch statement to emit the correct **OP_CODE** for **+**
- Our chunk now has everything we need to execute

##### 3. VM
- We start by reading the first byte which should always be an **OP_CODE**
- Now we'll use a switch statement to check what we should do
- In our case it will be **OP_CONST**
- We will read the constant by using the **IP** and then incrementing it then using that to get the value stored in the **value_array**
- We then push it on to the stack
- The next instruction will be **OP_CONST** and we repeat
  - This is because in **binary()** in the compiler we made sure to add the constant before the **OP_ADD**
- The next instruction will be **OP_ADD**
- We will pop the previous two constants off the stack, add them together then push that back on to the stack
- Because our interpeter is a prototype we just print the last value on the stack


## Chapter 20
### Hash Tables

####
