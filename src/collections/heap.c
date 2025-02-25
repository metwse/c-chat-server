#include "../../include/collections/heap.h"

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

#define PARENT_INDEX(i) (i - 1) / 2
#define LEFT_INDEX(i) i * 2 + 1


struct heap *heap_with_capacity(instance_ordering ordering, instance_drop drop,
                                size_t capacity)
{
    if (capacity < 1)
        return NULL;
    struct heap *heap = malloc(sizeof(struct heap));

    heap->drop = drop;
    heap->ordering = ordering;
    heap->capacity = capacity;
    heap->length = 0;
    heap->instances = calloc(sizeof(void *), 1);

    return heap;
}

struct heap *heap_new(instance_ordering ordering, instance_drop drop) 
{
    return heap_with_capacity(ordering, drop, 1);
}

void heap_drop(struct heap *h) 
{
    free(h->instances);
    free(h);
}

void heap_clear(struct heap *h) 
{
    h->length++;
    while (h->length--)
        h->drop(h->instances[h->length]);

    heap_drop(h);
}

bool heap_resize(struct heap *h, size_t size) 
{
    if (size < 1)
        return false;

    h->instances = realloc(h->instances, sizeof(void *) * size);
    h->capacity = size;
    if (size < h->length)
        h->length = size;
    
    return true;
}

bool heap_resize_by_freeing(struct heap *h, size_t size) 
{
    if (size < 1)
        return false;

    for (size_t i = h->capacity; i > h->capacity; i--) {
        void *instance = h->instances[i - 1];
        if (instance)
            h->drop(instance);
    }

    return heap_resize(h, size);
}

bool heap_insert(struct heap *h, void *instance) 
{
    if (h->capacity == h->length)
        heap_resize(h, h->length + 1);

    h->instances[h->length] = instance;

    size_t i = h->length;
    void *node = instance;

    while (i) {
        size_t parent = PARENT_INDEX(i);
        void *parent_node = h->instances[parent];

        if (h->ordering(parent_node, node) > 0) {
            h->instances[parent] = node;
            h->instances[i] = parent_node;
        } else 
            break;

        i = parent;
    }

    h->length++;

    return true;
}

void *heap_extract_root(struct heap *h) 
{
    if (!h->length)
        return NULL;
    
    void *root = h->instances[0];
    h->instances[0] = h->instances[h->length - 1];
    h->instances[h->length - 1] = NULL;
    h->length--;

    size_t i = 0;
    void *node = h->instances[0];

    while (i < h->length) {
        size_t left = LEFT_INDEX(i);
        if (left >= h->length) 
            break;

        void *left_node = h->instances[left];
        
        if (h->ordering(left_node, node) < 0) {
            h->instances[i] = left_node;
            h->instances[left] = node;
        } else 
            break;

        i = left;
    }

    return root;
}

bool heap_delete_root(struct heap *h) 
{
    void *instance = heap_extract_root(h);

    if (instance) 
        h->drop(instance);
    return !!instance;
}
