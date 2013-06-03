#include "linked_list.h"

#include "memory.h"

/* Linked list operations */

void linked_list_init(linked_list *list) {
	// Allocate a sentinel node
	linked_list_node *sentinel = safe_malloc(sizeof(linked_list_node));
	sentinel->next = NULL;
	list->head = sentinel;
}

linked_list_node *linked_list_head(linked_list *list) {
	return list->head->next;
}

void linked_list_append(linked_list *list, void *data) {
	linked_list_node *node = list->head;
	while(!linked_list_is_tail(linked_list_next(node))) {
		node = linked_list_next(node);
	}
	linked_list_node *new_node = safe_malloc(sizeof(linked_list_node));
	new_node->data = data;
	new_node->next = NULL;
	node->next = new_node;
}

void linked_list_free(linked_list *list) {
	linked_list_node *previous_node = list->head;
	linked_list_node *current_node;
	do {
		current_node = linked_list_next(previous_node);
		safe_free(previous_node);
		previous_node = current_node;
	} while(!linked_list_is_tail(current_node));

	list->head = NULL;
}

/* Linked list node operations */
bool linked_list_is_tail(linked_list_node *node) {
	return node == NULL;
}

linked_list_node *linked_list_next(linked_list_node *node) {
	return node->next;
}

void *linked_list_data(linked_list_node *node) {
	return node->data;
}
