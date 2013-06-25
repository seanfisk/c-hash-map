#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#include "memory.h"
#include "linked_list.h"

#include "hash_map.h"

// when "-g" is used redefine inline to static or else the linker will try to link the function and fail (since it's inline)
#ifdef TEST
#define inline static
#endif

inline int hash_map_default_comparator(const void *l, const void *r) {
	return *((unsigned long *) l) - *((unsigned long *) r);
}

inline size_t hash_map_default_hash_func(const void *key, size_t capacity) {
	return *((size_t *) key) % capacity;
}

void hash_map_init(hash_map *map, size_t capacity, hash_map_comparator comparator, hash_map_hash_func hash_func) {
	map->capacity = capacity;
	map->size = 0;

	map->table = (linked_list **) safe_malloc(sizeof(linked_list *) * map->capacity);
	memset(map->table, 0, sizeof(linked_list *) * map->capacity);

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

	map->keys = (linked_list *) safe_malloc(sizeof(linked_list));
	// No free_data func here because keys will be free'd by linked_list_free for **table
	linked_list_init(map->keys, NULL);
}

void hash_map_free(hash_map *map) {
	for (size_t i = 0; i < map->capacity; i++) {
		if (map->table[i]) {
			linked_list_free(map->table[i]);
		}
	}

	linked_list_free(map->keys);

	safe_free(map->table);

	safe_free(map);
}

void *hash_map_get(hash_map *map, void *key) {
	linked_list *list = map->table[map->hash_func(key, map->capacity)];

	if (!list) {
		return NULL;
	}

	linked_list_node *head = linked_list_head(list);

	while (head) {
		hash_map_pair *pair = (hash_map_pair *) head->data;

		if (map->comparator(pair->key, key) == 0) {
			return pair->value;
		}

		head = head->next;
	}

	return NULL;
}

void hash_map_put(hash_map *map, void *key, void *value) {
	linked_list *list = map->table[map->hash_func(key, map->capacity)];

	if (!list) {
		list = (linked_list *) safe_malloc(sizeof(linked_list));
		linked_list_init(list, (linked_list_destructor) safe_free);
		map->table[map->hash_func(key, map->capacity)] = list;
	}

	linked_list_node *head = linked_list_head(list);

	while (head) {
		hash_map_pair *pair = (hash_map_pair *) head->data;

		// if key already exists, update the value
		if (map->comparator(pair->key, key) == 0) {
			pair->value = value;
			return;
		}

		head = head->next;
	}

	// or else insert new one

	hash_map_pair *pair = (hash_map_pair *) safe_malloc(sizeof(hash_map_pair));
	pair->key = key;
	pair->value = value;

	linked_list_prepend(list, pair);

	linked_list_append(map->keys, key);

	map->size++;
}

void hash_map_remove(hash_map *map, void *key) {
	size_t offset = map->hash_func(key, map->capacity);
	linked_list *list = map->table[offset];

	if (!list) {
		return;
	}

	// The variable previous_node is set to the sentinel node, NOT the
	// head item of the list.
	linked_list_node *previous_node = list->head;
	linked_list_node *current_node = previous_node->next;
	while (true) {
		// Is the first node a match?
		if (map->comparator(((hash_map_pair *)current_node->data)->key, key) == 0) {
			// Delete the node and relink.
			previous_node->next = current_node->next;
			if (list->free_data) {
				list->free_data(current_node->data);
			}
			safe_free(current_node);
			// Decrement structure sizes
			list->size--;
			map->size--;
			return;
		}
		// Exit when we are at the end.
		if (current_node->next == NULL) {
			break;
		}
		// Increment
		previous_node = current_node;
		current_node = current_node->next;
	}
}

size_t hash_map_size(hash_map *map) {
	return map->size;
}

linked_list *hash_map_keys(hash_map *map) {
	return map->keys;
}

void hash_map_clear(hash_map *map) {
	for (size_t i = 0; i < map->capacity; i++) {
		linked_list *list = map->table[i];

		if (list) {
			linked_list_free(list);
			map->table[i] = NULL;
		}
	}

	map->size = 0;
}

bool hash_map_contains_key(hash_map *map, void *key) {
	linked_list *list = map->table[map->hash_func(key, map->capacity)];

	if (!list) {
		return false;
	}

	linked_list_node *head = linked_list_head(list);

	while (head) {
		hash_map_pair *pair = (hash_map_pair *) head->data;

		if (map->comparator(pair->key, key) == 0) {
			return true;
		}

		head = head->next;
	}

	return false;
}

