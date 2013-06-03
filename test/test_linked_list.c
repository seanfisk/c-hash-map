#include "linked_list.h"
#include "memory.h"

#include <unity.h>

static linked_list *list;

void setUp() {
	list = safe_malloc(sizeof(linked_list));
	linked_list_init(list);
}

void test_empty_list_node_is_tail() {
	TEST_ASSERT_TRUE(linked_list_is_tail(linked_list_head(list)));
}

void test_append() {
	const unsigned data_length = 4;
	int data[] = {111, 131, 35, 42};

	unsigned i;
	for(i = 0; i < data_length; ++i) {
		linked_list_append(list, &data[i]);
	}

	linked_list_node *node;
	for(
		i = 0, node = linked_list_head(list);
		!linked_list_is_tail(node);
		++i, node = linked_list_next(node)) {
		TEST_ASSERT_EQUAL_INT(data[i], *(int*)linked_list_data(node));
	}
}

void tearDown() {
	linked_list_free(list);
	safe_free(list);
}
