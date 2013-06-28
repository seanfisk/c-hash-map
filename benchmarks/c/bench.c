#include "timing.h"

#include "hash_map.h"
#include "memory.h"

#include <stdio.h>
#include <stdint.h>

static const uint64_t NUM_ITERS = 1e4;

static int int_cmp(uint64_t *a, uint64_t *b) {
	return (int)(*b - *a);
}

static void put() {
	hash_map map;
	hash_map_init(&map, NUM_ITERS, (hash_map_comparator) int_cmp, NULL);

	uint64_t *ints = safe_malloc(NUM_ITERS * sizeof(uint64_t));
	for(uint64_t i = 0; i < NUM_ITERS; ++i) {
		// Do this here so it's not counted in the time
		ints[i] = i;
	}

	start_timing();
	for(uint64_t i = 0; i < NUM_ITERS; ++i) {
		hash_map_put(&map, &ints[i], &ints[i]);
	}
	print_timing("put");

	safe_free(ints);
}

int main(int argc, char *argv[]) {
	puts("Our C hash map benchmark\n"
			 "All times are elapsed monotonic time.\n");
	put();
	return 0;
}
