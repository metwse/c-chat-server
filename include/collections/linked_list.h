/*! 
 * `linked_list` implements basic methods of linked list data structure.
 */

#ifndef COLLECTIONS_LINKED_LIST
#define COLLECTIONS_LINKED_LIST

#include <stddef.h>
#include <stdbool.h>
#include "traits.h"

/**
 * \brief linked_list struct
 */
struct linked_list_node {
    void *data;
    struct linked_list_node *next;
    struct linked_list_node *prev;
};

/**
 * \brief linked_list struct
 *
 * Implements fundemantal linked list methods.
 */
struct linked_list {
    instance_identify identify;
    instance_drop drop;
    struct linked_list_node *root;
    struct linked_list_node *last;
    size_t length;
};

/**
 * \brief Creates a new linked list.
 */
struct linked_list *linked_list_new(instance_identify, instance_drop);

/**
 * \brief Keeping its elements, drops the linked list.
 */
void linked_list_drop(struct linked_list *);

/**
 * \brief Drops the linked list freeing its elements.
 */
void linked_list_clear(struct linked_list *);

/**
 * \brief Inserts an element into linked list.
 */
bool linked_list_insert(struct linked_list *, void *element, size_t index);

/**
 * \brief Pushes an element into linked list.
 */
void linked_list_push(struct linked_list *, void *element);

/**
 * \brief Adds an element to the beginning of linked list.
 */
void linked_list_unshift(struct linked_list *, void *element);

/**
 * \brief Gets data from linked list by the index.
 */
void *linked_list_get(const struct linked_list *, size_t index);

/**
 * \brief Gets data from linked list by its id.
 */
void *linked_list_get_by_id(const struct linked_list *, char const *id);

/**
 * \brief Removes the instance from list, returs the instance.
 */
void *linked_list_remove(struct linked_list *, size_t index);

/**
 * \brief Removes and clears the instance by its index.
 */
bool linked_list_delete(struct linked_list *, size_t index);

/**
 * \brief Removes the instance from list by its id, returs the instance.
 */
void *linked_list_remove_by_id(struct linked_list *, char const *id);

/**
 * \brief Removes and clears the instance by its id.
 */
bool linked_list_delete_by_id(struct linked_list *, char const *id);

#endif
