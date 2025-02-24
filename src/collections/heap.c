#include "../../include/collections/heap.h"

#include <stdlib.h>
#include <string.h>


unsigned int parentOf(unsigned i) {
    return (i - 1) / 2;
}

unsigned int leftOf(unsigned i) {
    return i * 2 + 1;
}

unsigned int rightOf(unsigned i) {
    return i * 2 + 2;
}

Heap *Heap_withCapacity(instance_ordering ordering, instance_drop drop, unsigned int capacity) {
    if (capacity < 1) return NULL;

    Heap *heap = malloc(sizeof(Heap));

    heap->drop = drop;
    heap->ordering = ordering;
    heap->capacity = capacity;
    heap->length = 0;
    heap->instances = calloc(sizeof(void *), 1);

    return heap;
}

Heap *Heap_new(instance_ordering ordering, instance_drop drop) {
    return Heap_withCapacity(ordering, drop, 1);
}

char Heap_resize(Heap *h, unsigned int size) {
    if (size < 1) return 0;
    if (size < h->length)
        h->length = size;
    int diff = size - h->capacity;
    h->instances = realloc(h->instances, sizeof(void *) * size);
    if (diff > 0) memset(h->instances + h->length, 0, diff);
    h->capacity = size;
    return 1;
}

char Heap_resizeByFreeing(Heap *h, unsigned int size) {
    if (size < 1) return 0;
    for (unsigned int i = h->capacity; i > h->capacity; i--) {
        void *instance = h->instances[i - 1];
        if (instance) {
            h->drop(instance);
        }
    }
    return Heap_resize(h, size);
}

char Heap_insert(Heap *h, void *instance) {
    if (h->capacity == h->length)
        Heap_resize(h, h->length + 1);

    h->instances[h->length] = instance;

    unsigned i = h->length;
    void *currentNode = instance;
    while (i) {
        unsigned parent = parentOf(i);
        void *parentNode = h->instances[parent];
        if (h->ordering(parentNode, currentNode) > 0) {
            h->instances[parent] = currentNode;
            h->instances[i] = parentNode;
        } else break;
        i = parent;
    }

    h->length++;

    return 1;
}

void *Heap_extractRoot(Heap *h) {
    if (!h->length) return NULL;
    
    void *root = h->instances[0];
    h->instances[0] = h->instances[h->length - 1];
    h->instances[h->length - 1] = NULL;
    h->length--;

    unsigned int i = 0;
    void *currentNode = h->instances[0];
    while (i < h->length) {
        unsigned int left = leftOf(i);
        if (left >= h->length) break;
        void *leftNode = h->instances[left];
        
        if (h->ordering(leftNode, currentNode) < 0) {
            h->instances[i] = leftNode;
            h->instances[left] = currentNode;
        } else break;
        i = left;
    }

    return root;
}
