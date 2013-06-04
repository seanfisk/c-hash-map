#ifndef HASH_MAP_H
#define HASH_MAP_H

#include <stdlib.h>

typedef struct __hash_map {
	size_t capacity;
	void **table;
} hash_map;

void hash_map_init(hash_map *map);
void hash_map_free(hash_map *map);

void *hash_map_get(hash_map *map, void *key);
void hash_map_set(hash_map *map, void *key, void *value);


#endif // HASH_MAP_H

