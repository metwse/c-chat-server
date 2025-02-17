#include "../../include/collections/btree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

BTree* newBTree(Identifier identifier) {
    BTree* bt = malloc(sizeof(BTree));
    bt->root = NULL;
    bt->identifier = identifier;

    return bt;
}

Node* newNode(void *instance) {
    Node* node = malloc(sizeof(Node));
    node->gt = NULL;
    node->lt = NULL;
    node->instance = instance;

    return node;
}

char BTree_push(BTree *bt, void *instance) {
    const char *id = bt->identifier(instance);
    int idLen = strlen(id);
    if (idLen == 0) return 0;

    Node* createdNode = newNode(instance);

    if (!bt->root) {
        bt->root = createdNode;
        return 1;
    } else {
        Node* currentNode = bt->root;
        while (1) {
            const char *nodeId = bt->identifier(currentNode->instance);
            int cmp = strcmp(nodeId, id);

            if (cmp < 0) {
                if (!currentNode->lt) {
                    currentNode->lt = createdNode;
                    return 1;
                }
                currentNode = currentNode->lt;
                continue;
            }
            if (cmp > 0) {
                if (!currentNode->gt) {
                    currentNode->gt = createdNode;
                    return 1;
                }
                currentNode = currentNode->gt;
                continue;
            }
            return 0;
        }
    }
}

void* BTree_get(const BTree *bt, const char *id) {
    int idLen = strlen(id);
    if (idLen == 0) return 0;

    if (!bt->root) {
        return NULL;
    } else {
        Node* currentNode = bt->root;
        while (1) {
            const char *nodeId = bt->identifier(currentNode->instance);
            int cmp = strcmp(nodeId, id);

            if (cmp == 0) return currentNode->instance;

            if (cmp < 0 && currentNode->lt) currentNode = currentNode->lt;
            else if (cmp > 0 && currentNode->gt) currentNode = currentNode->gt;
            else return NULL;
        }
    }
}

int BTree_remove(BTree *bt, const char *id) {
    return 0;
}

int BTree_contains(const BTree *bt, const char *id) {
    return !!BTree_get(bt, id);
}
