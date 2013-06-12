#include "linked_list.h"

#include "memory.h"

/* Linked list operations */

void linked_list_init(linked_list *list, linked_list_comparator comparator, destructor free_node) {
	// Allocate a sentinel node
	linked_list_node *sentinel = safe_malloc(sizeof(linked_list_node));
	sentinel->next = NULL;
	list->head = sentinel;

	list->comparator = comparator;
	list->free_node = free_node;
}

linked_list_node *linked_list_head(linked_list *list) {
	return list->head->next;
}

void linked_list_append(linked_list *list, void *data) {
	linked_list_node *node = list->head;
	while(node->next) {
		node = node->next;
	}
	linked_list_node *new_node = safe_malloc(sizeof(linked_list_node));
	new_node->data = data;
	new_node->next = NULL;
	node->next = new_node;
}

void linked_list_prepend(linked_list *list, void *data) {
	linked_list_node *new_node = safe_malloc(sizeof(linked_list_node));
	new_node->data = data;
	new_node->next = list->head->next;
	list->head->next = new_node;
}

void linked_list_remove_first(linked_list *list, void *data) {
	linked_list_node *previous_node = list->head;
	linked_list_node *current_node = previous_node->next;
	while(true) {
		// Is the first node a match?
		if(list->comparator(current_node->data, data) == 0) {
			previous_node->next = current_node->next;
			safe_free(current_node);
			return;
		}
		// Exit when we are at the end.
		if(current_node->next == NULL) {
			break;
		}
		// Increment
		previous_node = current_node;
		current_node = current_node->next;
	}
}

void linked_list_free(linked_list *list) {
	linked_list_node *previous_node = list->head;
	linked_list_node *current_node = previous_node->next;

	while(current_node != NULL) {
		if(list->free_node != NULL) {
		    list->free_node(current_node->data);
		}
		safe_free(previous_node);
		previous_node = current_node;
		current_node = previous_node->next;
	}

	safe_free(previous_node);

	list->head = NULL;

	safe_free(list);
}
