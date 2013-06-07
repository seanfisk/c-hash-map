/**
 * @file
 */

#ifndef HASH_MAP_H
#define HASH_MAP_H

#include <stdlib.h>
#include <stdint.h>

#include "linked_list.h"

/**
 * Comparator function to determine whether *l and *r are equal
 * @return < 0 if *l is less than *r; == 0 if *l is equal to *r; > 0 if *l is greater than *r
 */
typedef int (*hash_map_comparator)(const void *l, const void *r);

/**
 * Hash function
 * @param key
 * @param capacity
 * @return the hash function should return an offset within the range [0, capacity)
 */
typedef size_t (*hash_map_hash_func)(const void *key, size_t capacity);

typedef struct __hash_map {
	size_t capacity;
	linked_list **table;

	hash_map_comparator comparator;
	hash_map_hash_func hash_func;
} hash_map;

/**
 * Key/value pair
 */
typedef struct __hash_map_pair {
	void *key;
	void *value;
} hash_map_pair;

/**
 * Initialize the hash map
 */
void hash_map_init(hash_map *map, size_t capacity, hash_map_comparator comparator, hash_map_hash_func hash_func);

/**
 * Free the hash map
 * this function will also free the table of internal linked lists
 */
void hash_map_free(hash_map *map);

/**
 * "get"
 */
void *hash_map_get(hash_map *map, void *key);

/**
 * "put"
 */
void hash_map_set(hash_map *map, void *key, void *value);

#endif // HASH_MAP_H

