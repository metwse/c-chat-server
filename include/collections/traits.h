#ifndef COLLECTIONS_TRAITS_H
#define COLLECTIONS_TRAITS_H

/**
 * Identifier type alias as a trait
 *
 * A function pointer that returns unique id for given instance.
 */
typedef const char *(*instance_identify)(void const *instance);

/**
 * \biref Drop type alias as a trait
 *
 * A function pointer that frees the memory allocated to the instance.
 */
typedef void (*instance_drop)(void *instance);

/**
 * \biref Ordering type alias as a trait
 *
 * Compares two instances.
 *
 * @return positive integer if instance1 is greater, 0 if both of the instances 
 *         are equal or negative integer if instance2 is greater.
 */
typedef int (*instance_ordering)(void const *instance1, void const *instance2);

#endif
