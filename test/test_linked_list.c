#include "linked_list.h"
#include "memory.h"

#include <unity.h>

static linked_list *list;

void setUp() {
	list = safe_malloc(sizeof(linked_list));
	linked_list_init(list);
}

void test_empty_list() {
	TEST_ASSERT_NULL(linked_list_head(list));
}

void test_append() {
	int data[] = {111, 131, 35, 42};

	unsigned i;
	for(i = 0; i < sizeof(data) / sizeof(*data); ++i) {
		linked_list_append(list, &data[i]);
	}

	linked_list_node *node;
	for(i = 0, node = linked_list_head(list); node != NULL; ++i, node = node->next) {
		TEST_ASSERT_EQUAL_INT(data[i], *(int*)node->data);
	}
}

void test_prepend() {
	int data[] = {111, 131, 35, 42};
	int data_length = sizeof(data) / sizeof(*data);

	unsigned i;
	for(i = 0; i < data_length; ++i) {
		linked_list_prepend(list, &data[i]);
	}

	linked_list_node *node;
	for(i = data_length-1, node = linked_list_head(list); node != NULL; --i, node = node->next) {
		TEST_ASSERT_EQUAL_INT(data[i], *(int*)node->data);
	}
}

void test_remove_first_beginning() {
	int data_before[] = {23, -37, -83, 92, 131, -13};
	int data_after[] = {-37, -83, 92, 131, -13};

	unsigned i;
	for(i = 0; i < sizeof(data_before) / sizeof(*data_before); ++i) {
		linked_list_append(list, &data_before[i]);
	}

	linked_list_remove_first(list, &data_before[0]);

	linked_list_node *node;
	for(i = 0, node = linked_list_head(list); node; ++i, node = node->next) {
		TEST_ASSERT_EQUAL_INT(data_after[i], *(int*)node->data);
	}
}

void test_remove_first_middle() {
	int data_before[] = {23, -37, -83, 92, 131, -13};
	int data_after[] = {23, -37, -83, 92, -13};

	unsigned i;
	for(i = 0; i < sizeof(data_before) / sizeof(*data_before); ++i) {
		linked_list_append(list, &data_before[i]);
	}

	linked_list_remove_first(list, &data_before[4]);

	linked_list_node *node;
	for(i = 0, node = linked_list_head(list); node; ++i, node = node->next) {
		TEST_ASSERT_EQUAL_INT(data_after[i], *(int*)node->data);
	}
}

void test_remove_first_end() {
	int data_before[] = {23, -37, -83, 92, 131, -13};
	int data_after[] = {23, -37, -83, 92, 131};

	unsigned i;
	for(i = 0; i < sizeof(data_before) / sizeof(*data_before); ++i) {
		linked_list_append(list, &data_before[i]);
	}

	linked_list_remove_first(list, &data_before[5]);

	linked_list_node *node;
	for(i = 0, node = linked_list_head(list); node; ++i, node = node->next) {
		TEST_ASSERT_EQUAL_INT(data_after[i], *(int*)node->data);
	}
}

void tearDown() {
	linked_list_free(list);
	safe_free(list);
}
