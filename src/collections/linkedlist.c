#include "../../include/collections/linkedlist.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>


LinkedList *LinkedList_new(instance_identify identify, instance_drop drop) {
    LinkedList *ll = malloc(sizeof(LinkedList));
    ll->root = NULL;
    ll->last = NULL;
    ll->identify = identify;
    ll->drop = drop;
    ll->length = 0;

    return ll;
};

void _LinkedList_drop(LinkedList *ll, int clearElements) {
    LinkedList_Node *node = ll->root;

    while (node) {
        LinkedList_Node *next = node->next;
        if (clearElements) ll->drop(node->data);
        free(node);
        node = next;
    }

    free(ll);
}

void LinkedList_drop(LinkedList *ll) {
    _LinkedList_drop(ll, 0);
}

void LinkedList_clear(LinkedList *ll) {
    _LinkedList_drop(ll, 1);
}

void LinkedList_push(LinkedList *ll, void *element) {
    LinkedList_Node *createdNode = malloc(sizeof(LinkedList_Node));

    createdNode->data = element;
    createdNode->next = NULL;
    createdNode->prev = ll->last;

    ll->length++;
    if (ll->root) ll->last->next = createdNode;
    else ll->root = createdNode;

    ll->last = createdNode;
}

void LinkedList_unshift(LinkedList *ll, void *element) {
    LinkedList_Node *createdNode = malloc(sizeof(LinkedList_Node));

    createdNode->data = element;
    createdNode->next = NULL;
    createdNode->prev = ll->root;

    ll->length++;
    createdNode->prev = ll->root;
    if (ll->root) ll->root->prev = createdNode;
    ll->root = createdNode;
}

void *removeElement(LinkedList *ll, LinkedList_Node *node, unsigned index) {
    if (node->prev) node->prev->next = node->next;
    if (node->next) node->next->prev = node->prev;

    if (index == ll->length - 1) ll->last = node->prev;
    if (index == 0) ll->root = node->next;

    ll->length--;

    void *data = node->data;
    free(node);
    return data;
}

void *LinkedList_get(const LinkedList *ll, unsigned index) {
    if (index >= ll->length) return NULL;

    LinkedList_Node *currentNode;
    if (index > (ll->length >> 1)) {
        currentNode = ll->last;
        index = ll->length - index - 1;
        while (index--) currentNode = currentNode->prev;
    } else {
        currentNode = ll->root;
        while (index--) currentNode = currentNode->next;
    }

    return currentNode->data;
}

void *LinkedList_getById(LinkedList const *ll, char const *id) {
    LinkedList_Node *currentNode = ll->root;

    while (currentNode->next) {
        if (!strcmp(ll->identify(currentNode->data), id))
            return currentNode->data;
        currentNode = currentNode->next;
    }

    return NULL;
}

void *LinkedList_remove(LinkedList *ll, unsigned index) {
    if (index >= ll->length) return NULL;

    LinkedList_Node *currentNode;
    unsigned i;
    if (index > (ll->length >> 1)) {
        currentNode = ll->last;
        i = ll->length - index - 1;
        while (i--) currentNode = currentNode->prev;
    } else {
        currentNode = ll->root;
        i = index;
        while (i--) currentNode = currentNode->next;
    }

    return removeElement(ll, currentNode, index);
}

void *LinkedList_removeById(LinkedList *ll, char const *id) {
    LinkedList_Node *currentNode = ll->root;

    unsigned index = 0;
    while (currentNode->next) {
        if (!strcmp(ll->identify(currentNode->data), id))
            return removeElement(ll, currentNode, index);
        index++;
        currentNode = currentNode->next;
    }

    return NULL;
}

char LinkedList_delete(LinkedList *ll, unsigned index) {
    void *data = LinkedList_remove(ll, index);
    if (data) ll->drop(data); 
    return !!data;
}

char LinkedList_deleteById(LinkedList *ll, char const *id) {
    void *data = LinkedList_removeById(ll, id);
    if (data) ll->drop(data); 
    return !!data;
}
