#ifndef TESTUTILS_COLLECTIONS_H
#define TESTUTILS_COLLECTIONS_H

/**
 * Sample struct that implements tratis of collections.
 */
struct test_collectable {
    char *id;
};

/**
 * Creates a new test collectable.
 */
struct test_collectable *test_collectable_new(char *);

/**
 * Returns id of the Collectable.
 */
const char *test_collectable_identify(void const *collectable);

/**
 * Compares two instances of collectables.
 */
int test_collectable_ordering(void const *collectable1,
                              void const *collectable2);

/**
 * Freeing the id field, drops Collectable.
 */
void test_collectable_drop(void *collectable);

#endif // !TESTUTILS_COLLECTIONS_H
