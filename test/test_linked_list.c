#include "linked_list.h"
#include "memory.h"

#include <unity.h>

#include <string.h>

static linked_list *list;

int intp_equal(const int *l, const int *r) {
	// Need to return 0 for equality, anything else for inequality.
	return *l - *r;
}

void setUp() {
	list = safe_malloc(sizeof(linked_list));
	linked_list_init(list, (linked_list_comparator)intp_equal);
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

	int to_remove = 23;
	linked_list_remove_first(list, &to_remove);

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

	int to_remove = 131;
	linked_list_remove_first(list, &to_remove);

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

	int to_remove = -13;
	linked_list_remove_first(list, &to_remove);

	linked_list_node *node;
	for(i = 0, node = linked_list_head(list); node; ++i, node = node->next) {
		TEST_ASSERT_EQUAL_INT(data_after[i], *(int*)node->data);
	}
}

void test_remove_string() {
	linked_list *list_str = safe_malloc(sizeof(linked_list));
	linked_list_init(list_str, (linked_list_comparator)strcmp);

	char *data_before[] = {"babak", "sean", "liu", "someone else"};
	char *data_after[] = {"babak", "liu", "someone else"};

	unsigned i;
	for(i = 0; i < sizeof(data_before) / sizeof(*data_before); ++i) {
		linked_list_append(list, data_before[i]);
	}

	linked_list_remove_first(list, "sean");

	linked_list_node *node;
	for(i = 0, node = linked_list_head(list); node; ++i, node = node->next) {
		TEST_ASSERT_EQUAL_STRING(data_after[i], (char*)node->data);
	}
}

void tearDown() {
	linked_list_free(list);
	safe_free(list);
}
