#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "memory.h"
#include "linked_list.h"

#include "hash_map.h"

int hash_map_default_comparator(const void *l, const void *r) {
	return *((unsigned long *) l) - *((unsigned long *) r);
}

size_t hash_map_default_hash_func(const void *key, size_t capacity) {
	return *((size_t *) key) % capacity;
}

void hash_map_init(hash_map *map, hash_map_comparator comparator, hash_map_hash_func hash_func) {
	map->capacity = 1000;
	map->table = (void **) safe_malloc(sizeof(void *) * map->capacity);

	memset(map->table, 0, sizeof(void *) * map->capacity);

	if (comparator) {
		map->comparator = comparator;
	} else {
		map->comparator = hash_map_default_comparator;
	}

	if (hash_func) {
		map->hash_func = hash_func;
	} else {
		map->hash_func = hash_map_default_hash_func;
	}
}

void hash_map_free(hash_map *map) {
	free(map);
}

void *hash_map_get(hash_map *map, void *key) {
	return map->table[map->hash_func(key, map->capacity)];
}

void hash_map_set(hash_map *map, void *key, void *value) {
	map->table[map->hash_func(key, map->capacity)] = value;
}

