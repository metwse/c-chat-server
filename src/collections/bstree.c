#include "../../include/collections/bstree.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>


void __bstree_recursive_drop(struct bstree_node *node, instance_drop drop)
{
    if (node->gt) 
        __bstree_recursive_drop(node->gt, drop);
    if (node->lt) 
        __bstree_recursive_drop(node->lt, drop);
    if (drop) 
        drop(node->instance);
}


struct bstree *bstree_new(instance_ordering ordering,
                          instance_identify identify,
                          instance_drop drop)
{
    struct bstree *bt = malloc(sizeof(struct bstree));
    bt->root = NULL;
    bt->ordering = ordering;
    bt->identify = identify;
    bt->drop = drop;

    return bt;
}

void bstree_drop(struct bstree *bt)
{
    __bstree_recursive_drop(bt->root, NULL);
    free(bt);
}

void bstree_clear(struct bstree *bt)
{
    __bstree_recursive_drop(bt->root, bt->drop);
    free(bt);
}

bool bstree_push(struct bstree *bt, void *instance)
{
    // const char *id = bt->identify(instance);
    // int id_len = strlen(id);
    // if (id_len == 0) return false;

    #define CREATE_NODE(var) { \
        var = malloc(sizeof(struct bstree_node)); \
        var->gt = NULL; \
        var->lt = NULL; \
        var->instance = instance; \
        return true; \
    }

    if (!bt->root)
        CREATE_NODE(bt->root);

    struct bstree_node *node = bt->root;
    while (true) {
        int cmp = bt->ordering(node->instance, instance);

        if (cmp < 0) {
            if (!node->lt)
                CREATE_NODE(node->lt);
            node = node->lt;
        } else if (cmp > 0) {
            if (!node->gt)
                CREATE_NODE(node->gt);
            node = node->gt;
        } else 
            return false;
    }
}

void *bstree_get(const struct bstree *bt, const char *id)
{
    int id_len = strlen(id);
    if (!id_len) 
        return NULL;

    if (!bt->root)
        return NULL;

    struct bstree_node *node = bt->root;
    while (1) {
        const char *node_id = bt->identify(node->instance);
        int cmp = strcmp(node_id, id);

        if (cmp == 0) 
            return node->instance;

        if (cmp < 0 && node->lt) 
            node = node->lt;
        else if (cmp > 0 && node->gt) 
            node = node->gt;
        else 
            return NULL;
    }
}

void *bstree_remove(struct bstree *bt, const char *id)
{
    int id_len = strlen(id);
    if (id_len == 0)
        return NULL;

    if (!bt->root)
        return NULL;

    struct bstree_node *parent = NULL;
    struct bstree_node *node = bt->root;
    int_fast8_t parent_direction = 0;

    while (1) {
        const char *node_id = bt->identify(node->instance);
        int cmp = strcmp(node_id, id);

        if (cmp == 0) 
            break;
        parent = node;

        if (cmp < 0 && node->lt) {
            node = node->lt;
            parent_direction = 0;
        } 
        else if (cmp > 0 && node->gt) {
            node = node->gt;
            parent_direction = 1;
        }
        else 
            return NULL;
    }

    void *instance;

    if (node->lt && node->gt) {
        struct bstree_node *successor_parent = node;
        struct bstree_node *successor = node->gt;
        int_fast8_t parent_direction = 1;

        while (successor->lt) {
            parent_direction = 0;
            successor_parent = successor;
            successor = successor->lt;
        }

        instance = node->instance;
        node->instance = successor->instance;

        if (parent_direction) 
            successor_parent->gt = successor->gt;
        else 
            successor_parent->lt = successor->gt;

        free(successor);
    } else { 
        struct bstree_node *overwriting_node = node->lt ? node->lt : node->gt;

        if (parent) 
            if (parent_direction) 
                parent->gt = overwriting_node;
            else 
                parent->lt = overwriting_node;
        else 
            bt->root = overwriting_node;

        instance = node->instance;
        free(node);
    }

    return instance;
}

bool bstree_delete(struct bstree *bt, const char *id)
{
    void *instance = bstree_remove(bt, id);
    if (instance) 
        bt->drop(instance);

    return !!instance;
}

bool bstree_contains(const struct bstree *bt, const char *id)
{
    return !!bstree_get(bt, id);
}
