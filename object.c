#include <stdio.h>
#include <string.h>

#include "memory.h"
#include "object.h"
#include "value.h"
#include "vm.h"

#define ALLOCATE_OBJ(type, object_type) \
    (type*)allocate_object(sizeof(type), object_type)

#define ALLOCATE_OBJ(type, object_type) \
    (type*)allocate_object(sizeof(type), object_type)

static Obj* allocate_object(size_t size, ObjType type) {
    Obj* object = (Obj*)reallocate(NULL, 0, size);
    object->type = type;
    return object;
}

static ObjString* allocate_string(char* chars, int length) {
    ObjString* string = ALLOCATE_OBJ(ObjString, OBJ_STRING);
    string->length = length;
    string->chars = chars;
    return string;
}

ObjString* copy_string(const char* chars, int length) {
    // Allocate just enough for all the chars and '\0'
    char* heap_chars = ALLOCATE(char, length + 1);
    // Now copy the chars from chars into the newly allocated memory
    memcpy(heap_chars, chars, length);
    heap_chars[length] = '\0'; // Duh
    return allocate_string(heap_chars, length);
}
