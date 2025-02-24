#include "collections.h"
#include <stdlib.h>
#include <string.h>


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

int Collectable_ordering(void const *collectable1, void const *collectable2) {
    return strcmp(((Collectable*) collectable1)->id, ((Collectable*) collectable2)->id);
}
