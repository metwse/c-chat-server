#include "collections.h"
#include <stdlib.h>
#include <string.h>


struct test_collectable *test_collectable_new(char *id) {
    struct test_collectable *c = malloc(sizeof(struct test_collectable));
    c->id = id;

    return c;
}

const char *test_collectable_identify(void const *test_collectable) {
    return ((struct test_collectable *) test_collectable)->id;
}

void test_collectable_drop(void *test_collectable) {
    free(((struct test_collectable *) test_collectable)->id);
    free(test_collectable);
}

int test_collectable_ordering(void const *test_collectable1, void const *test_collectable2) {
    return strcmp(((struct test_collectable *) test_collectable1)->id,
                  ((struct test_collectable *) test_collectable2)->id);
}
