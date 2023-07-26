#ifndef clox_memory_h
#define clox_memory_h

#include "common.h"

// 
#define ALLOCATE(type, count) \
    (type*)reallocate(NULL, 0, sizeof(type) * (count))

/* Grow capacity
 * ------------
 *  8 is a bit arbitrary. We could use any number.
 *  In order to choose the best constant, we need to know how often we're going to grow the array.
 *  And choose the best value for that.
 *  8 is also useful for when we start with an empty array.
 *
 *  Growing by 1.5x is a good choice because it's dynamic and it's not too aggressive.
 */
#define GROW_CAPACITY(capacity) \
    ((capacity) < 8 ? 8 : (capacity) * 2)

/* Grow array
 * ----------
 *  1. type // The type of the array elements
 *  2. pointer // The pointer to the array
 *  3. old_count // The old count of the array
 *  4. new_count // The new count of the array
 *
 *  1. Cast the pointer to the type of the array elements
 *  2. Reallocate the array to the new size
 *  3. The real work happens in reallocate
 */
#define GROW_ARRAY(type, pointer, old_count, new_count) \
    (type*)reallocate(pointer, sizeof(type) * (old_count), \
        sizeof(type) * (new_count))

#define FREE_ARRAY(type, pointer, old_count) \
    reallocate(pointer, sizeof(type) * (old_count), 0)

/* C - Note
 * --------
 * void* is a pointer to an unknown type.
 * it's useful when you want to pass around a pointer to some data, but you don't care what type it is.
 *
 * it may be dangerous because you lose type safety but can be quite useful
 */
void* reallocate(void* pointer, size_t old_size, size_t new_size);

#endif
