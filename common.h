#ifndef clox_common_h
#define clox_common_h

#define DEBUG_TRACE_EXECUTION

/*
 * This gives us the bool type, true and false constants.
 */
#include <stdbool.h>

/*
 * This gives us the NULL constant.
 * size_t is an unsigned integer type used to represent the size of objects. (returned by using sizeof)
 */
#include <stddef.h>

/*
 * This gives us the uint8_t type and the UINT8_MAX constant.
 * uint8_t is an unsigned integer type with width of exactly 8 bits.
 * UINT8_MAX is the maximum value representable by an object of type uint8_t.
 */
#include <stdint.h>

#endif
