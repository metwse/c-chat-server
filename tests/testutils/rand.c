#include "rand.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>


char _base_64_digit(unsigned num) {
    if (num < 10) return num + 48;
    else if (num < 36) return num + 55;
    else if (num < 62) return num + 61;
    else if (num == 62) return '-';
    else if (num == 63) return '_';
    return '0';
}

char *gen_identifier() {
    char *identifier = malloc(sizeof(char) * 24);

    unsigned timestamp = (unsigned)time(NULL);

    for (short i = 0; i < 6; i++)
        identifier[i] = _base_64_digit((timestamp >> (i * 6)) & 63);

    for (short i = 6; i < 23; i++)
        identifier[i] = _base_64_digit(rand() & 63);

    identifier[23] = '\0';

    return identifier;
}

char **gen_identifiers(unsigned count) {
    char **identifiers = malloc(sizeof(char *) * count);

    for (unsigned i = 0; i < count; i++)
        identifiers[i] = gen_identifier();

    return identifiers;
}
