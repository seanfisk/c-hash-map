/**
 * @file
 * Simple linked list implementation
 */

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdbool.h>
#include <stddef.h>

/**
 * Function to deallocate data pointers. For automatically allocated
 * memory, pass in `NULL` to call nothing. For memory allocated with
 * `malloc`, pass in `free`.
 */
typedef void (*linked_list_destructor)(const void *data);

/**
 * Linked list node structure
 */
typedef struct _linked_list_node {
	/** Pointer to the next node */
	struct _linked_list_node *next;
	/** Pointer to data */
	void *data;
} linked_list_node;

/**
 * Linked list object
 */
typedef struct {
	/** Pointer to sentinel node */
	linked_list_node *head;
	/** Function used to free data */
	linked_list_destructor free_data;
	/** Size of the linked_list */
	size_t size;
} linked_list;

/**
 * Initialize a linked list.
 * @param list linked list structure
 * @param comparator data comparator function
 * @param free_list data de-allocation function
 */
void linked_list_init(linked_list *list, linked_list_destructor free_list);

/**
 * Get the first linked list node.
 * @param list linked list structure
 * @return first linked list node
 */
linked_list_node *linked_list_head(linked_list *list);

/**
 * Append data to the list.
 * @param list linked list structure
 * @param data data to append
 */
void linked_list_append(linked_list *list, void *data);

/**
 * Prepend data to the list.
 * @param list linked list structure
 * @param data data to prepend
 */
void linked_list_prepend(linked_list *list, void *data);

/**
 * Free the linked list and all its nodes and data. Uses @ref
 * linked_list_destructor function passed to @ref linked_list_init
 * @param list linked list structure
 */
void linked_list_free(linked_list *list);

/**
 * Returns size of the linked list.
 * @param list linked list structure
 * @return size of list
 */
size_t linked_list_size(linked_list *list);

#endif
