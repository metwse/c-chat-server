#include "../../include/collections/bstree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

BSTree *BSTree_new(BSTree_Identifier identifier, BSTree_Remover remover) {
    BSTree *bt = malloc(sizeof(BSTree));
    bt->root = NULL;
    bt->identifier = identifier;
    bt->remover = remover;

    return bt;
}

Node *Node_new(void *instance) {
    Node *node = malloc(sizeof(Node));
    node->gt = NULL;
    node->lt = NULL;
    node->instance = instance;

    return node;
}

char BSTree_push(BSTree *bt, void *instance) {
    const char *id = bt->identifier(instance);
    int idLen = strlen(id);
    if (idLen == 0) return 0;

    Node *createdNode = Node_new(instance);

    if (!bt->root) {
        bt->root = createdNode;
        return 1;
    }

    Node *currentNode = bt->root;
    while (1) {
        const char *nodeId = bt->identifier(currentNode->instance);
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

    Node *currentNode = bt->root;
    while (1) {
        const char *nodeId = bt->identifier(currentNode->instance);
        int cmp = strcmp(nodeId, id);

        if (cmp == 0) return currentNode->instance;

        if (cmp < 0 && currentNode->lt) currentNode = currentNode->lt;
        else if (cmp > 0 && currentNode->gt) currentNode = currentNode->gt;
        else return NULL;
    }
}

int BSTree_remove(BSTree *bt, const char *id) {
    int idLen = strlen(id);
    if (idLen == 0) return 0;

    if (!bt->root) return 0;

    Node *parent = NULL;
    char parentDirection = 0;
    Node *currentNode = bt->root;
    while (1) {
        const char *nodeId = bt->identifier(currentNode->instance);
        int cmp = strcmp(nodeId, id);

        if (cmp == 0)  break;

        parent = currentNode;
        parentDirection = cmp > 0; 
        if (cmp < 0 && currentNode->lt) currentNode = currentNode->lt; 
        else if (cmp > 0 && currentNode->gt) currentNode = currentNode->gt;
        else return 0;
    }

    if (currentNode->lt && currentNode->gt) {
        Node *successorParent = currentNode;
        Node *successor = currentNode->gt;
        while (successor->lt) {
            successorParent = successor;
            successor = successor->lt;
        }
        bt->remover(currentNode->instance);
        currentNode->instance = successor->instance;
        if (successor->gt)
            successorParent->lt = successor->gt;
        free(successor);
        return 1;
    } 
    
    Node *overwritingNode = currentNode->lt ? currentNode->lt : currentNode->gt;
    bt->remover(currentNode->instance);

    if (parent) {
        if (parentDirection) parent->gt = overwritingNode;
        else parent->lt = overwritingNode;
    } else bt->root = overwritingNode;

    return 1;
}

int BSTree_contains(const BSTree *bt, const char *id) {
    return !!BSTree_get(bt, id);
}
