#include "memory.h"

#include <stdio.h>
#include <stdlib.h>

void *safe_malloc(size_t size) {
	void *ptr = malloc(size);

	if(!ptr) {
		fputs("out of memory", stderr);
		exit(1);
	}

	return ptr;
}

void safe_free(void *ptr ) {
	free(ptr);
}

