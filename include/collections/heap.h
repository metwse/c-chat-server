/*!
 * `struct heap` implements basic methods of heap data structure.
 */

#ifndef COLLECTIONS_HEAP_H
#define COLLECTIONS_HEAP_H

#include <stddef.h>
#include <stdbool.h>
#include "traits.h"

/**
 * \brief heap struct
 *
 * Implements basic heap methods.
 */
struct heap {
    instance_ordering ordering;
    instance_drop drop;
    void **instances;
    size_t length;
    size_t capacity;
};

/**
 * \brief Creates a new Heap.
 */
struct heap *heap_new(instance_ordering, instance_drop); 

/**
 * \brief Creates a new Heap with given capacity.
 */
struct heap *heap_with_capacity(instance_ordering, instance_drop,
                                size_t capacity); 

/**
 * \brief Keeping its instances, drops the heap.
 */
void heap_drop(struct heap *);

/**
 * \brief Drops the heap freeing its instances.
 */
void heap_clear(struct heap *);

/**
 * \brief Inserts the data into the heap.
 */
bool heap_insert(struct heap *, void *instance); 

/**
 * \brief Extracts root of the heap.
 */
void *heap_extract_root(struct heap *);

/**
 * \brief Extracts and clears root of the heap.
 */
bool heap_delete_root(struct heap *);

/**
 * \brief Resizes the heap. Removes elements if necessary.
 */
bool heap_resize(struct heap *, size_t size);

/**
 * \brief Resizes the heap. Removes and clears instances if they cannot fit
 * into the resized heap.
 */
bool heap_resize_by_freeing(struct heap *, size_t size);

#endif // !COLLECTIONS_HEAP_H
