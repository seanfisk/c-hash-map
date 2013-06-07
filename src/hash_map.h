/**
 * @file
 * Simple hash map implementation.
 */

#ifndef HASH_MAP_H
#define HASH_MAP_H

#include <stdlib.h>
#include <stdint.h>

#include "linked_list.h"

/**
 * Comparator function to determine whether `*l` and `*r` are equal.
 * @return Negative if `*l` is less than `*r`; zero if `*l` is equal to `*r`; positive if `*l` is greater than `*r`.
 */
typedef int (*hash_map_comparator)(const void *l, const void *r);

/**
 * Hash function
 * @param key key to hash
 * @param capacity maximum size of the map
 * @return an offset within the range `[0, capacity)`
 */
typedef size_t (*hash_map_hash_func)(const void *key, size_t capacity);

/**
 * Hash map object
 */
typedef struct {
	/** Maximum size of hash table */
	size_t capacity;
	/** Hash table */
	linked_list **table;
	/** Key comparator function */
	hash_map_comparator comparator;
	/** Key hash function */
	hash_map_hash_func hash_func;
} hash_map;

/**
 * Key/value pair
 */
typedef struct {
	/** Key */
	void *key;
	/** Value */
	void *value;
} hash_map_pair;

/**
 * Initialize the hash map.
 * @param map hash map structure
 * @param capacity maximum size of the hash map
 * @param comparator key comparator function
 * @param hash_func key hash function
 */
void hash_map_init(hash_map *map, size_t capacity, hash_map_comparator comparator, hash_map_hash_func hash_func);

/**
 * Free the hash map.
 * This function will also free the table of internal linked lists.
 * @param map hash map structure
 */
void hash_map_free(hash_map *map);

/**
 * Get the value for the given key.
 * @param map hash map structure
 * @param key key for value to fetch
 * @return pointer to the value
 */
void *hash_map_get(hash_map *map, void *key);

/**
 * Insert the value into the map.
 * @param map hash map structure
 * @param key key associated with value
 * @param value value associated with key
 */
void hash_map_set(hash_map *map, void *key, void *value);

#endif // HASH_MAP_H
