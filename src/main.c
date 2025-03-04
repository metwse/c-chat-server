#include "../include/net/server.h"

#include <stdlib.h>
#include <stdio.h>

#define ENV(VAR) char *VAR = getenv(#VAR); \
    if (!VAR) { \
        fprintf(stderr, "Cannot get environment variable %s\n", #VAR); \
        exit(1); \
    }


int main() 
{
    ENV(HOST);
    ENV(PORT);

    serve(HOST, strtol(PORT, NULL, 10));
}
