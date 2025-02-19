#include "../../include/collections/bstree.h"

#include <stdlib.h>
#include <string.h>


BSTree *BSTree_new(instance_identify identify, instance_drop drop) {
    BSTree *bt = malloc(sizeof(BSTree));
    bt->root = NULL;
    bt->identify = identify;
    bt->drop = drop;

    return bt;
}

BSTree_Node *Node_new(void *instance) {
    BSTree_Node *node = malloc(sizeof(BSTree_Node));
    node->gt = NULL;
    node->lt = NULL;
    node->instance = instance;

    return node;
}

char BSTree_push(BSTree *bt, void *instance) {
    const char *id = bt->identify(instance);
    int idLen = strlen(id);
    if (idLen == 0) return 0;

    BSTree_Node *createdNode = Node_new(instance);

    if (!bt->root) {
        bt->root = createdNode;
        return 1;
    }

    BSTree_Node *currentNode = bt->root;
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

void *BSTree_get(const BSTree *bt, const char *id) {
    int idLen = strlen(id);
    if (idLen == 0) return 0;

    if (!bt->root) return NULL;

    BSTree_Node *currentNode = bt->root;
    while (1) {
        const char *nodeId = bt->identify(currentNode->instance);
        int cmp = strcmp(nodeId, id);

        if (cmp == 0) return currentNode->instance;

        if (cmp < 0 && currentNode->lt) currentNode = currentNode->lt;
        else if (cmp > 0 && currentNode->gt) currentNode = currentNode->gt;
        else return NULL;
    }
}

char BSTree_remove(BSTree *bt, const char *id) {
    int idLen = strlen(id);
    if (idLen == 0) return 0;

    if (!bt->root) return 0;

    BSTree_Node *parent = NULL;
    int parentDirection = 0;
    BSTree_Node *currentNode = bt->root;
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
        BSTree_Node *successorParent = currentNode;
        BSTree_Node *successor = currentNode->gt;
        int parentDirection = 1;
        while (successor->lt) {
            parentDirection = 0;
            successorParent = successor;
            successor = successor->lt;
        }
        bt->drop(currentNode->instance);
        currentNode->instance = successor->instance;
        if (parentDirection) successorParent->gt = successor->gt;
        else successorParent->lt = successor->gt;
        free(successor);
        return 1;
    } 
    
    BSTree_Node *overwritingNode = currentNode->lt ? currentNode->lt : currentNode->gt;
    if (parent) 
        if (parentDirection) parent->gt = overwritingNode;
        else parent->lt = overwritingNode;
    else bt->root = overwritingNode;
    bt->drop(currentNode->instance);
    free(currentNode);

    return 1;
}

char BSTree_contains(const BSTree *bt, const char *id) {
    return !!BSTree_get(bt, id);
}
