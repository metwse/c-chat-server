#include "../include/net/server.h"
#include "../include/shared_state.h"

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

    struct shared_state *ss = initialize_shared_state();

    if (!ss) {
        fprintf(stderr, "Cannot initialize mutex");
        exit(1);
    }

    serve(HOST, strtol(PORT, NULL, 10), ss);
}
