#include "../../include/collections/heap.h"
#include "../testutils/collections.h"

#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <stdlib.h>


int main() {
    struct heap *h = heap_new(Collectable_ordering, Collectable_drop);

    char **identifiers = calloc(sizeof(char *), 4);

    for (uint8_t i = 0; i < 4; i++) {
        identifiers[i] =  calloc(sizeof(char), 2);
        sprintf(identifiers[i], "%c", 52 - (char) i);
    }

    printf("test: insert");
    for (uint8_t i = 0; i < 4; i++)
        heap_insert(h, Collectable_new(identifiers[i]));

    printf("test: extract");
    for (uint8_t i = 0; i < 4; i++)
        assert(((Collectable *) heap_extract_root(h))->id == identifiers[3 - i]);

    printf("test: deleteRoot");
    for (uint8_t i = 0; i < 4; i++)
        heap_insert(h, Collectable_new(identifiers[i]));

    for (uint8_t i = 0; i < 4; i++) assert(heap_delete_root(h));

    printf("test: drop");
    heap_drop(h);
}
