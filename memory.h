#ifndef clox_memory_h
#define clox_memory_h

#include "common.h"

/* Grow capacity
 * ------------
 *  8 is a bit arbitrary. We could use any number.
 *  In order to choose the best constant, we need to know how often we're going to grow the array.
 *  And choose the best value for that.
 *
 *  Growing by 1.5x is a good choice because it's dynamic and it's not too aggressive.
 */
#define GROW_CAPACITY(capacity) \
    ((capacity) < 8 ? 8 : (capacity) * 2)

#define GROW_ARRAY(type, pointer, old_count, new_count) \
    (type*)reallocate(pointer, sizeof(type) * (old_count), \
        sizeof(type) * (new_count))

void* reallocate(void* pointer, size_t old_size, size_t new_size);

#endif
