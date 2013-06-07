/**
 * @file
 * Memory allocation and de-allocation wrappers
 */

#ifndef MEMORY_H
#define MEMORY_H

#include <stddef.h>

#ifdef TEST
extern int __malloc_counter;
#endif

/**
 * Allocate memory while exiting on failure. Also used to count
 * references during testing. All code could call this instead of
 * `malloc`.
 * @param size amount of memory to allocate
 * @return pointer to allocated memory
 */
void *safe_malloc(size_t size);

/**
 * Pass-thru call to free. Also used to count references during
 * testing. All code should call this instead of `free`.
 * @param ptr pointer to de-allocate
 */
void safe_free(void *ptr);

#endif
