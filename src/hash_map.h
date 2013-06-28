/**
 * @file
 * Simple hash map implementation.
 */

#ifndef HASH_MAP_H
#define HASH_MAP_H

#include "linked_list.h"

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

/**
 * Comparator function to determine whether `*l` and `*r` are equal.
 * @return Negative if `*l` is less than `*r`; zero if `*l` is equal to `*r`; positive if `*l` is greater than `*r`.
 */
typedef int (*hash_map_comparator)(const void *l, const void *r);

/**
 * Hash function
 * @param key key to hash
 * @param capacity maximum size of the map
 * @param len the size of the key passed as the first argument
 * @return an offset within the range `[0, capacity)`
 */
typedef size_t (*hash_map_hash_func)(const void *key, size_t capacity, int len);

/**
 * Size function to determine the size of each keys in the hash function
 * @return the size of each key`
 */
typedef size_t (*hash_map_key_size)();

/**
 * Hash map object
 */
typedef struct {
	/** Maximum size of hash table */
	size_t capacity;
	/** Size of hash table */
	size_t size;
	/** Hash table */
	linked_list **table;
	/** Key comparator function */
	hash_map_comparator comparator;
	/** Key hash function */
	hash_map_hash_func hash_func;
	/** Key size function */
	hash_map_key_size key_size;
	/** Keys */
	linked_list *keys;
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
void hash_map_init(hash_map *map, size_t capacity, hash_map_comparator comparator, hash_map_hash_func hash_func, hash_map_key_size);

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
void hash_map_put(hash_map *map, void *key, void *value);

/**
 * Remove the mapping from the map if this key exists. Calling this on
 * a key for which there is no mapping does nothing (does not error).
 * @param map hash map structure
 * @param key key for mapping to remove
 */
void hash_map_remove(hash_map *map, void *key);

/**
 * Returns number of key-value pairs in the map
 * @param map hash map structure
 * @return size of the hash map
 */
size_t hash_map_size(hash_map *map);

/**
 * Returns a linked list that contains all keys in the map
 * @param map hash map structure
 * @return a linked list containing all keys
 */
linked_list *hash_map_keys(hash_map *map);

/**
 * Removes all key/value pairs from the map
 * @param map hash map structure
 */
void hash_map_clear(hash_map *map);

/**
 * Check if the map contains the given key
 * @param map hash map structure
 * @param key the key to check
 * @return true if map contains key
 */
bool hash_map_contains_key(hash_map *map, void *key);

#endif

