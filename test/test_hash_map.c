#include <string.h>

#include "hash_map.h"
#include "linked_list.h"

#include "memory.h"

#include <unity.h>

static hash_map *map;

void setUp() {
	map = safe_malloc(sizeof(hash_map));
	hash_map_init(map, (hash_map_comparator) strcmp, NULL);
}

void test_set_get() {
	hash_map_set(map, "key", "value");
	TEST_ASSERT_EQUAL_STRING("value", (char *) hash_map_get(map, "key"));

	hash_map_set(map, "key", "value2");
	TEST_ASSERT_EQUAL_STRING("value2", (char *) hash_map_get(map, "key"));

	hash_map_set(map, "key2", "value3");
	TEST_ASSERT_EQUAL_STRING("value3", (char *) hash_map_get(map, "key2"));
}

void test_get_invalid_key() {
	TEST_ASSERT_NULL(hash_map_get(map, "invalid_key"));
}

void test_hash_collision() {
	// these two hash obtained by default hash_func should be equal (since the first 8-byte is the same)
	TEST_ASSERT_EQUAL_UINT(map->hash_func("1234567890", map->capacity),
							map->hash_func("1234567809", map->capacity));

	// these two would collide and chaining should come into play
	hash_map_set(map, "1234567890", "9090");
	hash_map_set(map, "1234567809", "0909");

	TEST_ASSERT_EQUAL_STRING("9090", hash_map_get(map, "1234567890"));
	TEST_ASSERT_EQUAL_STRING("0909", hash_map_get(map, "1234567809"));
}

void tearDown() {
	hash_map_free(map);
}

