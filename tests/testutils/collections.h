#ifndef TESTUTILS_COLLECTIONS_H
#define TESTUTILS_COLLECTIONS_H

/**
 * Sample struct that implements tratis for collections.
 */
typedef struct Collectable {
    char *id;
} Collectable;

/**
 * Creates a new Collectable.
 */
Collectable *Collectable_new(char *);

/**
 * Returns id of the Collectable.
 */
const char *Collectable_identify(void const *collectable);

/**
 * Compares two instances of collectables.
 */
int Collectable_ordering(void const *collectable1, void const *collectable2);

/**
 * Freeing the id field, drops Collectable.
 */
void Collectable_drop(void *collectable);

#endif // !TESTUTILS_COLLECTIONS_H
