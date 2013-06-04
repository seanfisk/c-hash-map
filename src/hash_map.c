#include <stdlib.h>
#include <stdint.h>

#include "memory.h"

#include "hash_map.h"

void hash_map_init(hash_map *map) {
	map->capacity = 1000;
	map->table = (void **) safe_malloc(sizeof(void *) * map->capacity);
}

void hash_map_free(hash_map *map) {
	free(map);
}

void *hash_map_get(hash_map *map, void *key) {
	return map->table[(uint64_t) key % 1000];
}

void hash_map_set(hash_map *map, void *key, void *value) {
	map->table[(uint64_t) key % 1000] = value;
}

