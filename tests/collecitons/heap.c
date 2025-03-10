#include "../../include/collections/heap.h"
#include "../testutils/collections.h"

#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <stdlib.h>


int main() {
    struct heap *h = heap_new(test_collectable_ordering, test_collectable_drop);

    char **identifiers = calloc(sizeof(char *), 4);

    for (uint8_t i = 0; i < 4; i++) {
        identifiers[i] =  calloc(sizeof(char), 2);
        sprintf(identifiers[i], "%c", 52 - (char) i);
    }

    printf("test: insert\n");
    for (uint8_t i = 0; i < 4; i++)
        heap_insert(h, test_collectable_new(identifiers[i]));

    printf("test: extract\n");
    for (uint8_t i = 0; i < 4; i++)
        assert(((struct test_collectable *) heap_extract_root(h))->id == identifiers[3 - i]);

    printf("test: delete_root\n");
    for (uint8_t i = 0; i < 4; i++)
        heap_insert(h, test_collectable_new(identifiers[i]));

    for (uint8_t i = 0; i < 4; i++) assert(heap_delete_root(h));

    printf("test: drop\n");
    heap_drop(h);
}
