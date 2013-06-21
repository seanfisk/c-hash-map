#include "linked_list.h"

#include "memory.h"

void linked_list_init(linked_list *list, linked_list_destructor free_data) {
	// Allocate a sentinel node
	linked_list_node *sentinel = safe_malloc(sizeof(linked_list_node));
	sentinel->next = NULL;
	list->head = sentinel;

	list->free_data = free_data;

	list->size = 0;
}

linked_list_node *linked_list_head(linked_list *list) {
	return list->head->next;
}

void linked_list_append(linked_list *list, void *data) {
	linked_list_node *node = list->head;
	while (node->next) {
		node = node->next;
	}
	linked_list_node *new_node = safe_malloc(sizeof(linked_list_node));
	new_node->data = data;
	new_node->next = NULL;
	node->next = new_node;

	list->size++;
}

void linked_list_prepend(linked_list *list, void *data) {
	linked_list_node *new_node = safe_malloc(sizeof(linked_list_node));
	new_node->data = data;
	new_node->next = list->head->next;
	list->head->next = new_node;

	list->size++;
}

void linked_list_free(linked_list *list) {
	linked_list_node *previous_node = list->head;
	linked_list_node *current_node = previous_node->next;

	while (current_node != NULL) {
		if (list->free_data != NULL) {
			list->free_data(current_node->data);
		}
		safe_free(previous_node);
		previous_node = current_node;
		current_node = previous_node->next;
	}

	safe_free(previous_node);

	list->head = NULL;

	safe_free(list);
}

size_t linked_list_size(linked_list *list) {
	return list->size;
}
