#include <stdlib.h>

#include "memory.h"
#include "vm.h"

/**
 * Allocates a block of memory of the given size
 * @param size The size of the memory to allocate
 * @return A pointer to the allocated memory
 *
 * Old size | New size   | Action
 * ---------|----------- |-------
 *  0       | > 0        | Allocate new block
 *  > 0     | 0          | Free allocation
 *  > 0     | < old_size | Shrink allocation
 *  > 0     | > old_size | Grow allocation
 */
void* reallocate(void* pointer, size_t old_size, size_t new_size) {
    // If the new_size is zero that means we want to free the memory
    if (new_size == 0) {
        free(pointer);
        return NULL;
    }

    // We use C's realloc function to reallocate the memory
    // It takes a pointer to the old memory and the new size and returns a pointer to the new memory
    // We then cast the pointer to a void pointer and return it
    void* result = realloc(pointer, new_size);
    if (result == NULL) exit(1); // If the result is NULL that means the allocation failed
                                 // This can happen if the system is out of memory
                                 // There's nothing we can do about it so we just exit the program
    return result;
}

static void free_object(Obj* object) {
    switch (object->type) {
        case OBJ_STRING: {
            ObjString* string = (ObjString*)object;
            FREE_ARRAY(char, string->chars, string->length + 1);
            FREE(ObjString, object);
            break;
        }
    }
}

void free_objects() {
    Obj* object = vm.objects;
    while (object != NULL) {
        Obj* next = object->next;
        free_object(object);
        object = next;
    }
}

