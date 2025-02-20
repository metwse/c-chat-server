/*! 
 * `BSTree` implements basic methods of binary search tree struct.
 */

#ifndef COLLECTIONS_BSTREE_H
#define COLLECTIONS_BSTREE_H

#include "traits.h"

/**
 * \brief BSTree_Node struct
 * 
 * Data should implemet a char *identifier(void const *data) function which
 * returns an unique identifier for it.
 */
typedef struct BSTree_Node {
    struct BSTree_Node *gt;
    struct BSTree_Node *lt;
    void *instance;
} BSTree_Node;

/**
 * \brief Binary search tree struct
 */
typedef struct {
    instance_identify identify;
    instance_drop drop;
    BSTree_Node *root;
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
 * \brief Removes instance from the tree by its id.
 */
char BSTree_remove(BSTree *, const char *id);

/**
 * \brief Removes and clears instance tree by its id.
 */
char BSTree_delete(BSTree *, const char *id);

/**
 * \brief Check whether identifier contained in the BSTree.
 */
char BSTree_contains(const BSTree *, const char *id);

#endif // !COLLECTIONS_BSTREE_H
