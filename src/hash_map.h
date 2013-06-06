#ifndef HASH_MAP_H
#define HASH_MAP_H

#include <stdlib.h>
#include <stdint.h>

#include "linked_list.h"

typedef int (*hash_map_comparator)(const void *l, const void *r);
typedef size_t (*hash_map_hash_func)(const void *key, size_t capacity);

typedef struct __hash_map {
	size_t capacity;
	linked_list **table;

	hash_map_comparator comparator;
	hash_map_hash_func hash_func;
} hash_map;

typedef struct __hash_map_pair {
	void *key;
	void *value;
} hash_map_pair;

void hash_map_init(hash_map *map, size_t capacity, hash_map_comparator comparator, hash_map_hash_func hash_func);
void hash_map_free(hash_map *map);

void *hash_map_get(hash_map *map, void *key);
void hash_map_set(hash_map *map, void *key, void *value);

#endif // HASH_MAP_H

