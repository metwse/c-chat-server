/*! 
 * `BSTree` implements basic methods of binary search tree struct.
 */

#ifndef COLLECTIONS_BSTREE_H
#define COLLECTIONS_BSTREE_H

/**
 * \brief Identifier type alias as a trait
 *
 * A function pointer that returns unique id for given instance.
 */
typedef const char* (*BSTree_Identifier)(void *instance);

/**
 * Remover type alias as a trait
 *
 * A function pointer that frees the memory allocated to the instance.
 *
 * @param instance Instance identifier to be removed.
 */
typedef void (*BSTree_Remover)(void *instance);

/**
 * Node struct
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
 * BinaryTree struct
 */
typedef struct {
    BSTree_Identifier identifier;
    BSTree_Remover remover;
    Node *root;
} BSTree;

/**
 * Creates a new BSTree.
 */
BSTree *BSTree_new(BSTree_Identifier, BSTree_Remover);

/**
 * Pushes data into BSTree.
 */
char BSTree_push(BSTree *, void *instance);

/**
 * Gets data from BSTree.
 */
void *BSTree_get(const BSTree *, const char *id);

/**
 * Removes instance by its id.
 */
int BSTree_remove(BSTree *, const char *id);

/**
 * Check whether identifier contained in the BSTree.
 */
int BSTree_contains(const BSTree *, const char *id);

#endif // !COLLECTIONS_BSTREE_H
