#ifndef clox_value_h
#define clox_value_h

/* Constants
 * ---------
 *  We can store code in chunks but we also need to represent the values
 *
 *  For common things such as integers or floats, many instruction sets have
 *  a way to store them directly in the instructions.
 *  These instructions are called "immediate instructions" and the values are
 *  called "immediate values".
 *
 *  For larger values, we need to store them in the heap and store a pointer
 *  This is because the stack is limited in size and we don't want to overflow
 *  Also it is because we can't store 4 bytes into an odd address because of
 *  alignment issues.
 *
 *  For this interpreter, we'll use a single type to represent all values.
 *
 * Value
 * -----
 *  We can abstract the values in the language into a single type, Value.
 *  This is incase we want to change the representation of values in the future.
 *
 * Value array
 * -----------
 *  Each chunk will have a constant table that stores the values that are
 *  referenced by the instructions.
 *
 *  This constant table we'll call the "value array".
 *
 *  It has a capacity, count, and a pointer to the values (value array).
 */

#include "common.h"

typedef enum {
    VAL_BOOL,
    VAL_NIL,
    VAL_NUMBER,
} ValueType;

typedef struct {
    ValueType type;
    union {
        bool boolean;
        double number;
    } as;
} Value;

#define IS_BOOL(value) ((value).type == VAL_BOOL)
#define IS_NIL(value) ((value).type == VAL_NIL)
#define IS_NUMBER(value) ((value).type == VAL_NUMBER)

#define AS_BOOL(value) ((value).as.boolean)
#define AS_NUMBER(value) ((value).as.number)

#define BOOL_VAL(value) ((Value){VAL_BOOL, {.boolean = value}})
#define NIL_VAL ((Value){VAL_NIL, {.number = 0}})
#define NUMBER_VAL(value) ((Value){VAL_NUMBER, {.number = value}})

typedef struct {
  int capacity;
  int count;
  Value* values; // Array of pointers to values
} ValueArray;

bool values_equal(Value a, Value b);
void init_value_array(ValueArray* array);
void write_value_array(ValueArray* array, Value value);
void free_value_array(ValueArray* array);
void print_value(Value value);

#endif
