#include "../../include/collections/bstree.h"

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


struct bstree *bstree_new(instance_identify identify, instance_drop drop) {
    struct bstree *bt = malloc(sizeof(struct bstree));
    bt->root = NULL;
    bt->identify = identify;
    bt->drop = drop;

    return bt;
}

struct bstree_node *Node_new(void *instance) {
    struct bstree_node *node = malloc(sizeof(struct bstree_node));
    node->gt = NULL;
    node->lt = NULL;
    node->instance = instance;

    return node;
}

void _recursiveDrop(struct bstree_node *node, instance_drop drop) {
    if (node->gt) _recursiveDrop(node->gt, drop);
    if (node->lt) _recursiveDrop(node->lt, drop);
    if (drop) drop(node->instance);
}

void bstree_drop(struct bstree *bt) {
    _recursiveDrop(bt->root, NULL);
    free(bt);
}

void bstree_clear(struct bstree *bt) {
    _recursiveDrop(bt->root, bt->drop);
    free(bt);
}

bool bstree_push(struct bstree *bt, void *instance) {
    const char *id = bt->identify(instance);
    int idLen = strlen(id);
    if (idLen == 0) return 0;

    struct bstree_node *createdNode = Node_new(instance);

    if (!bt->root) {
        bt->root = createdNode;
        return 1;
    }

    struct bstree_node *currentNode = bt->root;
    while (1) {
        const char *nodeId = bt->identify(currentNode->instance);
        int cmp = strcmp(nodeId, id);

        if (cmp < 0) {
            if (!currentNode->lt) {
                currentNode->lt = createdNode;
                return 1;
            }
            currentNode = currentNode->lt;
        } else if (cmp > 0) {
            if (!currentNode->gt) {
                currentNode->gt = createdNode;
                return 1;
            }
            currentNode = currentNode->gt;
        } else return 0;
    }
}

void *bstree_get(const struct bstree *bt, const char *id) {
    int idLen = strlen(id);
    if (idLen == 0) return 0;

    if (!bt->root) return NULL;

    struct bstree_node *currentNode = bt->root;
    while (1) {
        const char *nodeId = bt->identify(currentNode->instance);
        int cmp = strcmp(nodeId, id);

        if (cmp == 0) return currentNode->instance;

        if (cmp < 0 && currentNode->lt) currentNode = currentNode->lt;
        else if (cmp > 0 && currentNode->gt) currentNode = currentNode->gt;
        else return NULL;
    }
}

void *bstree_remove(struct bstree *bt, const char *id) {
    int idLen = strlen(id);
    if (idLen == 0) return NULL;

    if (!bt->root) return NULL;

    struct bstree_node *parent = NULL;
    int parentDirection = 0;
    struct bstree_node *currentNode = bt->root;
    while (1) {
        const char *nodeId = bt->identify(currentNode->instance);
        int cmp = strcmp(nodeId, id);

        if (cmp == 0)  break;
        parent = currentNode;

        if (cmp < 0 && currentNode->lt) {
            currentNode = currentNode->lt;
            parentDirection = 0;
        } 
        else if (cmp > 0 && currentNode->gt) {
            currentNode = currentNode->gt;
            parentDirection = 1;
        }
        else return 0;
    }

    if (currentNode->lt && currentNode->gt) {
        struct bstree_node *successorParent = currentNode;
        struct bstree_node *successor = currentNode->gt;
        int parentDirection = 1;
        while (successor->lt) {
            parentDirection = 0;
            successorParent = successor;
            successor = successor->lt;
        }
        void *instance = currentNode->instance;
        currentNode->instance = successor->instance;
        if (parentDirection) successorParent->gt = successor->gt;
        else successorParent->lt = successor->gt;
        free(successor);

        return instance;
    } 
    
    struct bstree_node *overwritingNode = currentNode->lt ? currentNode->lt : currentNode->gt;
    if (parent) 
        if (parentDirection) parent->gt = overwritingNode;
        else parent->lt = overwritingNode;
    else bt->root = overwritingNode;
    void *instance = currentNode->instance;
    free(currentNode);

    return instance;
}

bool bstree_delete(struct bstree *bt, const char *id) {
    void *instance = bstree_remove(bt, id);
    if (instance) bt->drop(instance);
    return !!instance;
}

bool bstree_contains(const struct bstree *bt, const char *id) {
    return !!bstree_get(bt, id);
}
