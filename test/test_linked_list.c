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
	for(i = 0, node = linked_list_head(list); node; ++i, node = node->next) {
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
	for(i = data_length-1, node = linked_list_head(list); node; --i, node = node->next) {
		TEST_ASSERT_EQUAL_INT(data[i], *(int*)node->data);
	}
}


void tearDown() {
	linked_list_free(list);
	safe_free(list);
}
