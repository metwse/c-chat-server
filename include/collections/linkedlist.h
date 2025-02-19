/*! 
 * `LinkedList` implements basic methods of linked list struct.
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
 * \brief Removes instance by its index.
 */
char LinkedList_remove(LinkedList *, unsigned index);

/**
 * \brief Gets data from LinkedList by its id.
 */
void *LinkedList_getById(const LinkedList *, char const *id);

/**
 * \brief Removes instance by its index.
 */
char LinkedList_removeById(LinkedList *, char const *id);

#endif // !COLLECTIONS_LINKED_LIST
