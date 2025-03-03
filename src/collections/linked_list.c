#include "../../include/collections/linked_list.h"

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>


static inline struct linked_list_node *__get_node(const struct linked_list *ll,
                                                  size_t index) 
{
    if (index >= ll->length) 
        return NULL;

    struct linked_list_node *node;
    if (index > (ll->length >> 1)) {
        node = ll->last;
        index = ll->length - index - 1;
        while (index--) node = node->prev;
    } else {
        node = ll->root;
        while (index--) node = node->next;
    }

    return node;
}

static inline struct linked_list_node *__get_node_by_id(const struct linked_list *ll,
                                                        const char *id) 
{
    struct linked_list_node *node = ll->root;

    while (node->next) {
        if (!strcmp(ll->identify(node->data), id))
            return node;
        node = node->next;
    }

    return NULL;
}

static inline void *__remove_node(struct linked_list *ll,
                                  struct linked_list_node *node) 
{
    if (node->prev) node->prev->next = node->next;
    else ll->root = node->next;
    if (node->next) node->next->prev = node->prev;
    else ll->last = node->prev;

    ll->length--;

    void *data = node->data;
    free(node);
    return data;
}

static inline void __drop_linked_list(struct linked_list *ll, bool free_elements)
{
    struct linked_list_node *node = ll->root;

    while (node) {
        struct linked_list_node *next = node->next;
        if (free_elements) ll->drop(node->data);
        free(node);

        node = next;
    }

    free(ll);
}


struct linked_list *linked_list_new(instance_identify identify,
                                    instance_drop drop) 
{
    struct linked_list *ll = malloc(sizeof(struct linked_list));
    ll->root = NULL;
    ll->last = NULL;
    ll->identify = identify;
    ll->drop = drop;
    ll->length = 0;

    return ll;
};

void linked_list_drop(struct linked_list *ll) 
{
    __drop_linked_list(ll, 0);
}

void linked_list_clear(struct linked_list *ll) 
{
    __drop_linked_list(ll, 1);
}

void *linked_list_get(const struct linked_list *ll, size_t index) 
{
    struct linked_list_node *node = __get_node(ll, index);

    if (node) 
        return node->data;
    return NULL;
}

void *linked_list_get_by_id(struct linked_list const *ll, char const *id) 
{
    struct linked_list_node *node = __get_node_by_id(ll, id);

    if (node) 
        return node->data;
    return NULL;
}

void *linked_list_remove(struct linked_list *ll, size_t index) 
{
    if (index >= ll->length) 
        return NULL;

    return __remove_node(ll, __get_node(ll, index));
}

void *linked_list_remove_by_id(struct linked_list *ll, char const *id) 
{
    struct linked_list_node *node = __get_node_by_id(ll, id);

    if (node) 
        return __remove_node(ll, node);
    return NULL;
}

bool linked_list_delete(struct linked_list *ll, size_t index)
{
    void *data = linked_list_remove(ll, index);

    if (data) ll->drop(data); 
    return !!data;
}

bool linked_list_delete_by_id(struct linked_list *ll, char const *id)
{
    void *data = linked_list_remove_by_id(ll, id);

    if (data) ll->drop(data); 
    return !!data;
}

bool linked_list_insert(struct linked_list *ll, void *element, size_t index) 
{
    if (index > ll->length)
        return false;

    struct linked_list_node *new_node = malloc(sizeof(struct linked_list_node));

    new_node->data = element;
    new_node->prev = index ? __get_node(ll, index - 1) : NULL;
    new_node->next = __get_node(ll, index);

    if (!new_node->prev)
        ll->root = new_node;
    if (!new_node->next)
        ll->last = new_node;

    if (new_node->prev)
        new_node->prev->next = new_node;
    if (new_node->next)
        new_node->next->prev = new_node;

    ll->length++;

    return true;
}

void linked_list_push(struct linked_list *ll, void *element) 
{
    linked_list_insert(ll, element, ll->length);
}

void linked_list_unshift(struct linked_list *ll, void *element) 
{
    linked_list_insert(ll, element, 0);
}
