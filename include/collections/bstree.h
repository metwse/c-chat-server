/*! 
 * `bstree` implements basic methods of binary search tree data structure.
 */

#ifndef COLLECTIONS_BSTREE_H
#define COLLECTIONS_BSTREE_H

#include <stdbool.h>
#include "traits.h"

/**
 * bstree_node struct
 * 
 * Data should implemet a char *identifier(void const *data) function which
 * returns an unique identifier for it.
 */
struct bstree_node {
    struct bstree_node *gt;
    struct bstree_node *lt;
    void *instance;
};

/**
 * Binary search tree struct
 */
struct bstree {
    instance_ordering ordering;
    instance_identify identify;
    instance_drop drop;
    struct bstree_node *root;
};

/**
 * Creates a new bstree.
 */
struct bstree *bstree_new(instance_ordering, instance_identify, instance_drop);

/**
 * Keeping its instances, drops the tree.
 */
void bstree_drop(struct bstree *);

/**
 * Drops the tree freeing its instances.
 */
void bstree_clear(struct bstree *);

/**
 * Pushes data into bstree.
 */
bool bstree_push(struct bstree *, void *instance);

/**
 * Gets data from bstree.
 */
void *bstree_get(const struct bstree *, const char *id);

/**
 * Removes instance from the tree by its id.
 */
void *bstree_remove(struct bstree *, const char *id);

/**
 * Removes and clears instance tree by its id.
 */
bool bstree_delete(struct bstree *, const char *id);

/**
 * Check whether identifier contained in the bstree.
 */
bool bstree_contains(const struct bstree *, const char *id);

#endif
