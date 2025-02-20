/*! 
 * `LinkedList` implements basic methods of linked list data structure.
 */

#ifndef COLLECTIONS_LINKED_LIST
#define COLLECTIONS_LINKED_LIST

#include "traits.h"

/**
 * \brief LinkedList_Node struct
 */
typedef struct LinkedList_Node {
    void *data;
    struct LinkedList_Node *next;
    struct LinkedList_Node *prev;
} LinkedList_Node;

/**
 * \brief LinkedList struct
 *
 * Implements fundemantal linked list methods.
 */
typedef struct LinkedList {
    instance_identify identify;
    instance_drop drop;
    LinkedList_Node *root;
    LinkedList_Node *last;
    unsigned length;
} LinkedList;

/**
 * \brief Creates a new LinkedList.
 */
LinkedList *LinkedList_new(instance_identify, instance_drop);

/**
 * \brief Keeping its elements, drops the linked list.
 */
void LinkedList_drop(LinkedList *);

/**
 * \brief Drops the linked list freeing its elements.
 */
void LinkedList_clear(LinkedList *);

/**
 * \brief Pushes an element into LinkedList.
 */
void LinkedList_push(LinkedList *, void *element);

/**
 * \brief Adds an element to the beginning of LinkedList.
 */
void LinkedList_unshift(LinkedList *, void *element);

/**
 * \brief Gets data from LinkedList by the index.
 */
void *LinkedList_get(const LinkedList *, unsigned index);

/**
 * \brief Gets data from LinkedList by its id.
 */
void *LinkedList_getById(const LinkedList *, char const *id);

/**
 * \brief Removes the instance from list, returs the instance.
 */
void *LinkedList_remove(LinkedList *, unsigned index);

/**
 * \brief Removes and clears the instance by its index.
 */
char LinkedList_delete(LinkedList *, unsigned index);

/**
 * \brief Removes the instance from list by its id, returs the instance.
 */
void *LinkedList_removeById(LinkedList *, char const *id);

/**
 * \brief Removes and clears the instance by its id.
 */
char LinkedList_deleteById(LinkedList *, char const *id);

#endif // !COLLECTIONS_LINKED_LIST
