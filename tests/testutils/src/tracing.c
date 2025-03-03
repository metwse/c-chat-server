#include "../tracing.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>


const struct tracing *tracing_new(const char *scope) 
{
    struct tracing *t = malloc(sizeof(struct tracing));
    t->scope = scope;
    t->span_count = 0;
    t->spans = NULL;

    return t;
}

const struct tracing *tracing_span(const struct tracing *t, const char *scope) 
{
    struct tracing *t2 = malloc(sizeof(struct tracing));
    t2->scope = t->scope;
    t2->span_count = t->span_count + 1;
    t2->spans = calloc(sizeof(char *), t2->span_count);

    for (int_fast32_t i = 0; i < t->span_count; i++) 
        t2->spans[i] = t->spans[i];

    t2->spans[t->span_count] = scope;
    
    return t2;
}

void tracing_log(const struct tracing *t) {
    printf("[%s]", t->scope);

    for (int_fast32_t i = 0; i < t->span_count; i++)
        printf(" > %s", t->spans[i]);

    printf(": ");
}
