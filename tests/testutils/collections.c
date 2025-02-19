#include "collections.h"
#include <stdlib.h>

Collectable *Collectable_new(char *id) {
    Collectable *c = malloc(sizeof(Collectable));
    c->id = id;

    return c;
}

const char *Collectable_identify(void const *collectable) {
    return ((Collectable*) collectable)->id;
}

void Collectable_drop(void *collectable) {
    free(((Collectable*) collectable)->id);
    free(collectable);
}
