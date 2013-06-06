#include "hash_map.h"
#include "memory.h"

#include <unity.h>

static hash_map *map;

void setUp() {
	map = safe_malloc(sizeof(hash_map));
	hash_map_init(map, NULL, NULL);
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

void tearDown() {
	hash_map_free(map);
}

