#include <string.h>
#include <stdint.h>

#include "hash_map.h"
#include "linked_list.h"

#include "memory.h"

#include <unity.h>

static hash_map *map;

extern int __malloc_counter;

void setUp() {
	map = safe_malloc(sizeof(hash_map));
	hash_map_init(map, 1000, (hash_map_comparator) strcmp, NULL);
}

void test_size() {
	TEST_ASSERT_EQUAL_UINT(0, hash_map_size(map));

	hash_map_put(map, "key", "value");
	TEST_ASSERT_EQUAL_UINT(1, hash_map_size(map));

	hash_map_put(map, "key2", "value");
	TEST_ASSERT_EQUAL_UINT(2, hash_map_size(map));

	// if the same key was updated, size should not change
	hash_map_put(map, "key", "value2");
	TEST_ASSERT_EQUAL_UINT(2, hash_map_size(map));

	// if hashs collide, size should still work
	hash_map_put(map, "1234567890", "9090");
	hash_map_put(map, "1234567809", "0909");
	TEST_ASSERT_EQUAL_UINT(4, hash_map_size(map));

	hash_map_remove(map, "key");
	hash_map_remove(map, "key2");
	hash_map_remove(map, "1234567890");
	hash_map_remove(map, "1234567809");
	TEST_ASSERT_EQUAL_UINT(0, hash_map_size(map));
}

void test_put_get() {
	hash_map_put(map, "key", "value");
	TEST_ASSERT_EQUAL_STRING("value", (char *) hash_map_get(map, "key"));

	hash_map_put(map, "key", "value2");
	TEST_ASSERT_EQUAL_STRING("value2", (char *) hash_map_get(map, "key"));

	hash_map_put(map, "key2", "value3");
	TEST_ASSERT_EQUAL_STRING("value3", (char *) hash_map_get(map, "key2"));
}

void test_get_invalid_key() {
	TEST_ASSERT_NULL(hash_map_get(map, "invalid_key"));
}

void test_default_hash_func() {
	uint64_t i1 = 1, i2 = 1001;

	// these two should collide because of the %
	TEST_ASSERT_EQUAL_UINT(map->hash_func(&i1, map->capacity),
	                       map->hash_func(&i2, map->capacity));

	// these two hash obtained by default hash_func should be equal (since the first 8-byte is the same)
	TEST_ASSERT_EQUAL_UINT(map->hash_func("1234567890", map->capacity),
	                       map->hash_func("1234567809", map->capacity));

}

void test_collision() {
	// these two would collide and chaining should come into play
	hash_map_put(map, "1234567890", "9090");
	hash_map_put(map, "1234567809", "0909");

	TEST_ASSERT_EQUAL_STRING("9090", hash_map_get(map, "1234567890"));
	TEST_ASSERT_EQUAL_STRING("0909", hash_map_get(map, "1234567809"));
}

void test_put_remove() {
	hash_map_put(map, "abcd", "the alphabet");
	hash_map_put(map, "1234", "some numbers");

	hash_map_remove(map, "abcd");
	hash_map_remove(map, "1234");

	TEST_ASSERT_NULL(hash_map_get(map, "abcd"));
	TEST_ASSERT_NULL(hash_map_get(map, "1234"));

	hash_map_put(map, "abcd", "try it again");
	TEST_ASSERT_EQUAL_STRING("try it again", hash_map_get(map, "abcd"));
}

void test_remove_non_existent() {
	hash_map_remove(map, "not here");
	TEST_ASSERT_EQUAL_UINT(0, hash_map_size(map));
}

void test_clear() {
	hash_map_put(map, "key", "value");
	hash_map_put(map, "key2", "value2");
	hash_map_put(map, "key3", "value3");

	hash_map_clear(map);

	TEST_ASSERT_EQUAL_UINT(0, hash_map_size(map));

	TEST_ASSERT_NULL(hash_map_get(map, "key"));
	TEST_ASSERT_NULL(hash_map_get(map, "key2"));
	TEST_ASSERT_NULL(hash_map_get(map, "key3"));
}

void test_keys() {
	char *keys[] = { "key", "keys2", "1234567890", "1234567809" };
	char *values[] = { "value", "value2", "9090", "0909" };

	linked_list *keys_list = hash_map_keys(map);
	TEST_ASSERT_EQUAL_UINT(0, linked_list_size(keys_list));

	for (int i = 0; i < sizeof(keys) / sizeof(*keys); i++) {
		hash_map_put(map, keys[i], values[i]);
	}

	keys_list = hash_map_keys(map);
	TEST_ASSERT_EQUAL_UINT(4, linked_list_size(keys_list));

	linked_list_node *node = linked_list_head(keys_list);
	for (int i = 0; i < sizeof(keys) / sizeof(*keys); i++) {
		TEST_ASSERT_EQUAL_STRING(keys[i], node->data);
		node = node->next;
	}
}

void test_contains_key() {
	hash_map_put(map, "key", "value");
	hash_map_put(map, "key2", "value2");
	hash_map_put(map, "null key", NULL);

	TEST_ASSERT_TRUE(hash_map_contains_key(map, "key"));
	TEST_ASSERT_TRUE(hash_map_contains_key(map, "key2"));

	TEST_ASSERT_FALSE(hash_map_contains_key(map, "not here"));

	TEST_ASSERT_TRUE(hash_map_contains_key(map, "null key"));
}

void tearDown() {
	hash_map_free(map);

	TEST_ASSERT_EQUAL_INT(__malloc_counter, 0);
}

