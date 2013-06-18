#include "memory.h"

#include <stdio.h>
#include <stdlib.h>

#ifdef TEST
int __malloc_counter = 0;
#endif

void *safe_malloc(size_t size) {
	void *ptr = malloc(size);

	if (!ptr) {
		fputs("out of memory", stderr);
		exit(1);
	}

#ifdef TEST
	//printf("malloc: %p, counter: %d\n", ptr, __malloc_counter);
	__malloc_counter++;
#endif

	return ptr;
}

void safe_free(void *ptr) {
	free(ptr);
#ifdef TEST
	__malloc_counter--;
	//printf("free: %p, counter: %d\n", ptr, __malloc_counter);
#endif
}
