#include "../../include/collections/linkedlist.h"

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>


struct linked_list *linked_list_new(instance_identify identify, instance_drop drop) {
    struct linked_list *ll = malloc(sizeof(struct linked_list));
    ll->root = NULL;
    ll->last = NULL;
    ll->identify = identify;
    ll->drop = drop;
    ll->length = 0;

    return ll;
};

void _linked_list_drop(struct linked_list *ll, int clearElements) {
    struct linked_list_node *node = ll->root;

    while (node) {
        struct linked_list_node *next = node->next;
        if (clearElements) ll->drop(node->data);
        free(node);
        node = next;
    }

    free(ll);
}

void linked_list_drop(struct linked_list *ll) {
    _linked_list_drop(ll, 0);
}

void linked_list_clear(struct linked_list *ll) {
    _linked_list_drop(ll, 1);
}

void linked_list_push(struct linked_list *ll, void *element) {
    struct linked_list_node *createdNode = malloc(sizeof(struct linked_list_node));

    createdNode->data = element;
    createdNode->next = NULL;
    createdNode->prev = ll->last;

    ll->length++;
    if (ll->root) ll->last->next = createdNode;
    else ll->root = createdNode;

    ll->last = createdNode;
}

void linked_list_unshift(struct linked_list *ll, void *element) {
    struct linked_list_node *createdNode = malloc(sizeof(struct linked_list_node));

    createdNode->data = element;
    createdNode->next = NULL;
    createdNode->prev = ll->root;

    ll->length++;
    createdNode->prev = ll->root;
    if (ll->root) ll->root->prev = createdNode;
    ll->root = createdNode;
}

void *removeElement(struct linked_list *ll, struct linked_list_node *node, size_t index) {
    if (node->prev) node->prev->next = node->next;
    if (node->next) node->next->prev = node->prev;

    if (index == ll->length - 1) ll->last = node->prev;
    if (index == 0) ll->root = node->next;

    ll->length--;

    void *data = node->data;
    free(node);
    return data;
}

void *linked_list_get(const struct linked_list *ll, size_t index) {
    if (index >= ll->length) return NULL;

    struct linked_list_node *currentNode;
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

void *linked_list_get_by_id(struct linked_list const *ll, char const *id) {
    struct linked_list_node *currentNode = ll->root;

    while (currentNode->next) {
        if (!strcmp(ll->identify(currentNode->data), id))
            return currentNode->data;
        currentNode = currentNode->next;
    }

    return NULL;
}

void *linked_list_remove(struct linked_list *ll, size_t index) {
    if (index >= ll->length) return NULL;

    struct linked_list_node *currentNode;
    size_t i;
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

void *linked_list_remove_by_id(struct linked_list *ll, char const *id) {
    struct linked_list_node *currentNode = ll->root;

    unsigned index = 0;
    while (currentNode->next) {
        if (!strcmp(ll->identify(currentNode->data), id))
            return removeElement(ll, currentNode, index);
        index++;
        currentNode = currentNode->next;
    }

    return NULL;
}

bool linked_list_delete(struct linked_list *ll, size_t index) {
    void *data = linked_list_remove(ll, index);
    if (data) ll->drop(data); 
    return !!data;
}

bool linked_list_delete_by_id(struct linked_list *ll, char const *id) {
    void *data = linked_list_remove_by_id(ll, id);
    if (data) ll->drop(data); 
    return !!data;
}
