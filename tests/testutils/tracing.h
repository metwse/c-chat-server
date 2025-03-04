#ifndef TRACING

#define TRACING(SCOPE) SCOPE = tracing_new(#SCOPE);
#define SPAN(SCOPE, SPAN) const struct tracing *SPAN = tracing_span(SCOPE, #SPAN);
#define LOG(SPAN, ...) tracing_log(SPAN); \
    printf(__VA_ARGS__); \
    printf("\n");

#include <stdio.h>
#include <stddef.h>


struct tracing {
    const char *scope;
    const char **spans;
    size_t span_count;
};

const struct tracing *tracing_new(const char *);

const struct tracing *tracing_span(const struct tracing *, const char *);

void tracing_log(const struct tracing *);

#endif
