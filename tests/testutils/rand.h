#ifndef TESTUTILS_RAND_H
#define TESTUTILS_RAND_H

/**
 * Generates unique identifier using system's time. Generated identifier does
 * not need to be universally unique, being unique during program execution is
 * enough.
 */
char *gen_identifier();

/**
 * Generates n identifiers.
 */
char **gen_identifiers(unsigned);

#endif // !TESTUTILS_RAND_H
