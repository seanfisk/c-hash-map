#ifndef MEMORY_H
#define MEMORY_H

#include <stddef.h>

void *safe_malloc(size_t size);
void safe_free(void *ptr);

#endif /* MEMORY_H */
