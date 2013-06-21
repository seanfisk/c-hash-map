#include "linked_list.h"
#include "memory.h"

#include <unity.h>
#include <stdlib.h>

#include <string.h>

static linked_list *list;
static linked_list *dynamic_list;

void setUp() {
	list = safe_malloc(sizeof(linked_list));

	linked_list_init(list, (linked_list_destructor) NULL);

	dynamic_list = safe_malloc(sizeof(linked_list));
	linked_list_init(dynamic_list, (linked_list_destructor) safe_free);
}

void test_empty_list() {
	TEST_ASSERT_NULL(linked_list_head(list));
	TEST_ASSERT_NULL(linked_list_head(dynamic_list));
}

void test_append() {
	int data[] = {111, 131, 35, 42};

	unsigned i;
	for (i = 0; i < sizeof(data) / sizeof(*data); ++i) {
		linked_list_append(list, &data[i]);
	}

	linked_list_node *node;
	for (i = 0, node = linked_list_head(list); node != NULL; ++i, node = node->next) {
		TEST_ASSERT_EQUAL_INT(data[i], *(int *)node->data);
	}
}

void test_append_dynamic() {
	int data_length = 6;

	int i;
	for (i = 0; i < data_length; ++i) {
		int *data = (int *) safe_malloc(sizeof(int));
		*data = i * 100;
		linked_list_append(dynamic_list, data);
	}

	linked_list_node *node;
	for (i = 0, node = linked_list_head(dynamic_list); node != NULL; ++i, node = node->next) {
		TEST_ASSERT_EQUAL_INT(i * 100, *(int *)node->data);
	}
}

void test_prepend() {
	int data[] = {111, 131, 35, 42};
	int data_length = sizeof(data) / sizeof(*data);

	unsigned i;
	for (i = 0; i < data_length; ++i) {
		linked_list_prepend(list, &data[i]);
	}

	linked_list_node *node;
	for (i = data_length - 1, node = linked_list_head(list); node != NULL; --i, node = node->next) {
		TEST_ASSERT_EQUAL_INT(data[i], *(int *)node->data);
	}
}

void test_prepend_dynamic() {
	int data_length = 6;

	int i;
	for (i = 0; i < data_length; ++i) {
		int *data = (int *) safe_malloc(sizeof(int));
		*data = i * 100;
		linked_list_prepend(dynamic_list, data);
	}

	linked_list_node *node;
	for (i = data_length - 1, node = linked_list_head(dynamic_list); node != NULL; --i, node = node->next) {
		TEST_ASSERT_EQUAL_INT(i * 100, *(int *)node->data);
	}
}

void test_size() {
	TEST_ASSERT_EQUAL_UINT(0, linked_list_size(list));

	int data[] = { 2, 4, 5, 9 };
	for (int i = 0; i < sizeof(data) / sizeof(*data); i++) {
		linked_list_append(list, &data[i]);
	}
	TEST_ASSERT_EQUAL_UINT(4, linked_list_size(list));
}

void tearDown() {
	linked_list_free(list);
	linked_list_free(dynamic_list);

	TEST_ASSERT_EQUAL_INT(__malloc_counter, 0);
}
