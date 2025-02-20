/*!
 * `Heap` implements basic methods of heap data structure.
 */

#ifndef COLLECTIONS_HEAP_H
#define COLLECTIONS_HEAP_H

#include "traits.h"

/**
 * \brief Heap struct
 *
 * Implements basic heap methods.
 */
typedef struct {
    instance_ordering ordering;
    instance_drop drop;
    void **instances;
    unsigned length;
    unsigned capacity;
} Heap;

/**
 * \brief Creates a new Heap.
 */
Heap *Heap_new(instance_ordering, instance_drop); 

/**
 * \brief Creates a new Heap with given capacity.
 */
Heap *Heap_withCapacity(instance_ordering, instance_drop, unsigned capacity); 

/**
 * \brief Keeping its instances, drops the heap.
 */
void Heap_drop(Heap *);

/**
 * \brief Drops the heap freeing its instances.
 */
void Heap_clear(Heap *);

/**
 * \brief Inserts the data into the heap.
 */
char Heap_insert(Heap *, void *instance); 

/**
 * \brief Extracts root of the heap.
 */
void *Heap_extract(Heap *);

/**
 * \brief Extracts and clears root of the heap.
 */
char Heap_shift(Heap *);

/**
 * \brief Resizes the heap. Removes elements if necessary.
 */
char Heap_resize(Heap *, unsigned size);

/**
 * \brief Resizes the heap. Removes  and clears instances if necessary.
 */
char Heap_resizeByFreeing(Heap *, unsigned size);

#endif // !COLLECTIONS_HEAP_H
