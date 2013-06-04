#ifndef _LINKED_LIST_H_
#define _LINKED_LIST_H_

#include <stdbool.h>

typedef struct linked_list_node_tag {
	struct linked_list_node_tag *next;
	void *data;
} linked_list_node;

typedef struct {
	linked_list_node *head;
} linked_list;

/* Linked list operations */
void linked_list_init(linked_list *list);
linked_list_node *linked_list_head(linked_list *list);
void linked_list_append(linked_list *list, void *data);
void linked_list_prepend(linked_list *list, void *data);
void linked_list_free(linked_list *list);

#endif /* _LINKED_LIST_H_ */
