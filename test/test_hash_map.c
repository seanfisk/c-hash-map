#include <string.h>
#include <stdint.h>

#include "hash_map.h"
#include "hash_functions.h"
#include "linked_list.h"

#include "memory.h"

#include <unity.h>

static hash_map **hash_map_array;
const int hash_map_array_size = 2;

extern int __malloc_counter;

void setUp() {
	hash_map_array = (hash_map **) safe_malloc(sizeof(hash_map *) * hash_map_array_size);
	// hash_map_array[0] : using default hash function
	// hash_map_array[1] : using Pearson hash function

	for (int i = 0; i < hash_map_array_size; i++) {
		hash_map_array[i] = safe_malloc(sizeof(hash_map));
	}

	hash_map_init(hash_map_array[0], 1000, (hash_map_comparator) strcmp, NULL, strlen);
	hash_map_init(hash_map_array[1], 1000, (hash_map_comparator) strcmp, xPear16, strlen);
}

void test_size() {
	hash_map *this_hash_map;

	for (int i = 0; i < hash_map_array_size; i++) {
		this_hash_map = hash_map_array[i];

		TEST_ASSERT_EQUAL_UINT(0, hash_map_size(this_hash_map));

		hash_map_put(this_hash_map, "key", "value");
		TEST_ASSERT_EQUAL_UINT(1, hash_map_size(this_hash_map));

		hash_map_put(this_hash_map, "key2", "value");
		TEST_ASSERT_EQUAL_UINT(2, hash_map_size(this_hash_map));

		// if hashs collide, size should still work
		hash_map_put(this_hash_map, "1234567890", "9090");
		hash_map_put(this_hash_map, "1234567809", "0909");
		TEST_ASSERT_EQUAL_UINT(4, hash_map_size(this_hash_map));

		hash_map_remove(this_hash_map, "key");
		hash_map_remove(this_hash_map, "key2");
		hash_map_remove(this_hash_map, "1234567890");
		hash_map_remove(this_hash_map, "1234567809");
		TEST_ASSERT_EQUAL_UINT(0, hash_map_size(this_hash_map));
	}
}

void test_put_get() {
	hash_map *this_hash_map;

	for (int i = 0; i < hash_map_array_size; i++) {
		this_hash_map = hash_map_array[i];

		hash_map_put(this_hash_map, "key", "value");
		TEST_ASSERT_EQUAL_STRING("value", (char *) hash_map_get(this_hash_map, "key"));

		hash_map_put(this_hash_map, "key", "value2");
		TEST_ASSERT_EQUAL_STRING("value2", (char *) hash_map_get(this_hash_map, "key"));

		hash_map_put(this_hash_map, "key2", "value3");
		TEST_ASSERT_EQUAL_STRING("value3", (char *) hash_map_get(this_hash_map, "key2"));
	}
}

void test_get_invalid_key() {
	hash_map *this_hash_map;

	for (int i = 0; i < hash_map_array_size; i++) {
		this_hash_map = hash_map_array[i];

		TEST_ASSERT_NULL(hash_map_get(this_hash_map, "invalid_key"));
	}
}

int int_size() {
	return sizeof(uint64_t);
}


void test_default_hash_func() {
	uint64_t i1 = 1, i2 = 1001;

	hash_map *this_hash_map;

	for (int i = 0; i < hash_map_array_size; i++) {
		this_hash_map = hash_map_array[i];

		// these two should collide because of the %
		TEST_ASSERT_EQUAL_UINT(this_hash_map->hash_func(&i1, this_hash_map->capacity, int_size()),
		                       this_hash_map->hash_func(&i2, this_hash_map->capacity, int_size()));

		// these two hash obtained by default hash_func should be equal (since the first 8-byte is the same)
		TEST_ASSERT_EQUAL_UINT(this_hash_map->hash_func("1234567890", this_hash_map->capacity, int_size()),
		                       this_hash_map->hash_func("1234567809", this_hash_map->capacity, int_size()));
	}

}

void test_collision() {
	hash_map *this_hash_map;

	for (int i = 0; i < hash_map_array_size; i++) {
		this_hash_map = hash_map_array[i];

		// these two would collide and chaining should come into play
		hash_map_put(this_hash_map, "1234567890", "9090");
		hash_map_put(this_hash_map, "1234567809", "0909");

		TEST_ASSERT_EQUAL_STRING("9090", hash_map_get(this_hash_map, "1234567890"));
		TEST_ASSERT_EQUAL_STRING("0909", hash_map_get(this_hash_map, "1234567809"));
	}
}

void test_put_remove() {
	hash_map *this_hash_map;

	for (int i = 0; i < hash_map_array_size; i++) {
		this_hash_map = hash_map_array[i];

		hash_map_put(this_hash_map, "abcd", "the alphabet");
		hash_map_put(this_hash_map, "1234", "some numbers");

		hash_map_remove(this_hash_map, "abcd");
		hash_map_remove(this_hash_map, "1234");

		TEST_ASSERT_NULL(hash_map_get(this_hash_map, "abcd"));
		TEST_ASSERT_NULL(hash_map_get(this_hash_map, "1234"));

		hash_map_put(this_hash_map, "abcd", "try it again");
		TEST_ASSERT_EQUAL_STRING("try it again", hash_map_get(this_hash_map, "abcd"));
	}
}

void test_remove_non_existent() {
	hash_map *this_hash_map;

	for (int i = 0; i < hash_map_array_size; i++) {
		this_hash_map = hash_map_array[i];

		hash_map_remove(this_hash_map, "not here");
		TEST_ASSERT_EQUAL_UINT(0, hash_map_size(this_hash_map));
	}
}

void test_clear() {
	hash_map *this_hash_map;

	for (int i = 0; i < hash_map_array_size; i++) {
		this_hash_map = hash_map_array[i];

		hash_map_put(this_hash_map, "key", "value");
		hash_map_put(this_hash_map, "key2", "value2");
		hash_map_put(this_hash_map, "key3", "value3");

		hash_map_clear(this_hash_map);

		TEST_ASSERT_EQUAL_UINT(0, hash_map_size(this_hash_map));

		TEST_ASSERT_NULL(hash_map_get(this_hash_map, "key"));
		TEST_ASSERT_NULL(hash_map_get(this_hash_map, "key2"));
		TEST_ASSERT_NULL(hash_map_get(this_hash_map, "key3"));
	}
}

void test_keys() {
	char *keys[] = { "key", "keys2", "1234567890", "1234567809" };
	char *values[] = { "value", "value2", "9090", "0909" };

	hash_map *this_hash_map;

	for (int i = 0; i < hash_map_array_size; i++) {
		this_hash_map = hash_map_array[i];

		linked_list *keys_list = hash_map_keys(this_hash_map);
		TEST_ASSERT_EQUAL_UINT(0, linked_list_size(keys_list));

		for (int i = 0; i < sizeof(keys) / sizeof(*keys); i++) {
			hash_map_put(this_hash_map, keys[i], values[i]);
		}

		keys_list = hash_map_keys(this_hash_map);
		TEST_ASSERT_EQUAL_UINT(4, linked_list_size(keys_list));

		linked_list_node *node = linked_list_head(keys_list);
		for (int i = 0; i < sizeof(keys) / sizeof(*keys); i++) {
			TEST_ASSERT_EQUAL_STRING(keys[i], node->data);
			node = node->next;
		}
	}
}

void test_contains_key_empty_map() {
	hash_map *this_hash_map;

	for (int i = 0; i < hash_map_array_size; i++) {
		this_hash_map = hash_map_array[i];

		TEST_ASSERT_FALSE(hash_map_contains_key(this_hash_map, "no keys in map"));
	}
}

void test_contains_key_null_key() {
	hash_map *this_hash_map;

	for (int i = 0; i < hash_map_array_size; i++) {
		this_hash_map = hash_map_array[i];

		hash_map_put(this_hash_map, "null key", NULL);
		TEST_ASSERT_TRUE(hash_map_contains_key(this_hash_map, "null key"));
	}
}

void test_contains_key_nonexistent_key() {
	hash_map *this_hash_map;

	for (int i = 0; i < hash_map_array_size; i++) {
		this_hash_map = hash_map_array[i];

		TEST_ASSERT_FALSE(hash_map_contains_key(this_hash_map, "not here"));
	}
}

void test_contains_key_multiple() {
	hash_map *this_hash_map;

	for (int i = 0; i < hash_map_array_size; i++) {
		this_hash_map = hash_map_array[i];

		hash_map_put(this_hash_map, "key", "value");
		hash_map_put(this_hash_map, "key2", "value2");

		TEST_ASSERT_TRUE(hash_map_contains_key(this_hash_map, "key"));
		TEST_ASSERT_TRUE(hash_map_contains_key(this_hash_map, "key2"));
	}
}

void tearDown() {
	hash_map *this_hash_map;

	for (int i = 0; i < hash_map_array_size; i++) {
		this_hash_map = hash_map_array[i];
		hash_map_free(this_hash_map);

	}
	safe_free(hash_map_array);

	TEST_ASSERT_EQUAL_INT(__malloc_counter, 0);
}
