#ifndef COLLECTIONS_BTREE_H
#define COLLECTIONS_BTREE_H


/**
 * Identifier type alias
 *
 * A function pointer that returns unique id for given instance.
 */
typedef const char* (*Identifier)(void* instance);

/**
 * Node struct
 * 
 * data should implemet a char *identifier(DataType const* data) function which
 * returns an unique identifier for it.
 */
typedef struct Node {
    struct Node* gt;
    struct Node* lt;
    void* instance;
} Node;

/**
 * BinaryTree struct
 */
typedef struct {
    Identifier identifier;
    Node* root;
} BTree;

/**
 * Creates a new BTree.
 */
BTree* newBTree(Identifier);

/**
 * Pushes data into BTree.
 */
char BTree_push(BTree *, void *instance);

/**
 * Gets data from BTree.
 */
void* BTree_get(const BTree *, const char *id);

/**
 * Removes instance by its id.
 */
int BTree_remove(BTree *, const char *id);

/**
 * Check whether identifier contained in the BTree.
 */
int BTree_contains(const BTree *, const char *id);

#endif // !COLLECTIONS_BTREE_H
