#ifndef HASH_MAP_H
#define HASH_MAP_H

#include <stdlib.h>
#include <stdint.h>

typedef int (*hash_map_comparator)(const void *l, const void *r);
typedef size_t (*hash_map_hash_func)(const void *key, size_t capacity);

typedef struct __hash_map {
	size_t capacity;
	void **table;

	hash_map_comparator comparator;
	hash_map_hash_func hash_func;
} hash_map;

void hash_map_init(hash_map *map, hash_map_comparator comparator, hash_map_hash_func hash_func);
void hash_map_free(hash_map *map);

void *hash_map_get(hash_map *map, void *key);
void hash_map_set(hash_map *map, void *key, void *value);


#endif // HASH_MAP_H

