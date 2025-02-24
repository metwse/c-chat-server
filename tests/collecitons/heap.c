#include "../../include/collections/heap.h"
#include "../testutils/collections.h"

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>


int main() {
    Heap *h = Heap_new(Collectable_ordering, Collectable_drop);

    char **identifiers = calloc(sizeof(char *), 4);

    for (unsigned int i = 0; i < 4; i++) {
        identifiers[i] =  calloc(sizeof(char), 2);
        sprintf(identifiers[i], "%c", 52 - (char) i);
    }

    printf("test: insert");
    for (unsigned int i = 0; i < 4; i++)
        Heap_insert(h, Collectable_new(identifiers[i]));

    printf("test: extract");
    for (unsigned int i = 0; i < 4; i++)
        assert(((Collectable *) Heap_extractRoot(h))->id == identifiers[3 - i]);

    printf("test: deleteRoot");
    for (unsigned int i = 0; i < 4; i++)
        Heap_insert(h, Collectable_new(identifiers[i]));

    for (unsigned int i = 0; i < 4; i++) assert(Heap_deleteRoot(h));

    printf("test: drop");
    Heap_drop(h);
}
