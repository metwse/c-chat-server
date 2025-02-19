/*! 
 * `BSTree` implements basic methods of binary search tree struct.
 */

#ifndef COLLECTIONS_BSTREE_H
#define COLLECTIONS_BSTREE_H

#include "traits.h"

/**
 * \brief Node struct
 * 
 * data should implemet a char *identifier(DataType const* data) function which
 * returns an unique identifier for it.
 */
typedef struct Node {
    struct Node *gt;
    struct Node *lt;
    void *instance;
} Node;

/**
 * \brief Binary search tree struct
 */
typedef struct {
    instance_identify identify;
    instance_drop drop;
    Node *root;
} BSTree;

/**
 * \brief Creates a new BSTree.
 */
BSTree *BSTree_new(instance_identify, instance_drop);

/**
 * \brief Pushes data into BSTree.
 */
char BSTree_push(BSTree *, void *instance);

/**
 * \brief Gets data from BSTree.
 */
void *BSTree_get(const BSTree *, const char *id);

/**
 * \brief Removes instance by its id.
 */
int BSTree_remove(BSTree *, const char *id);

/**
 * \brief Check whether identifier contained in the BSTree.
 */
int BSTree_contains(const BSTree *, const char *id);

#endif // !COLLECTIONS_BSTREE_H
