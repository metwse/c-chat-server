#ifndef COLLECTIONS_TRAITS_H
#define COLLECTIONS_TRAITS_H

/**
 * \brief Identifier type alias as a trait
 *
 * A function pointer that returns unique id for given instance.
 */
typedef const char* (*instance_identify)(void const *instance);

/**
 * \biref Remover type alias as a trait
 *
 * A function pointer that frees the memory allocated to the instance.
 */
typedef void (*instance_drop)(void *instance);

#endif // !COLLECTIONS_TRAITS_H
