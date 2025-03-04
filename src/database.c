#include "../include/database.h"

#include <stdlib.h>
#include <string.h>


const char *user_identify(const void *u) 
{
    return ((struct user *) u)->username;
}

int user_ordering(void const *u1, void const *u2) {
    return strcmp(user_identify(u1), user_identify(u2));
}

const char *channel_identify(const void *c) 
{
    return ((struct channel *) c)->channel_name;
}

int channel_ordering(void const *c1, void const *c2) {
    return strcmp(channel_identify(c1), channel_identify(c2));
}

const char *connection_identify(const void *c) 
{
    unsigned len = sizeof(int) / sizeof(char);
    char *buf = malloc(len + 1);
    memcpy(buf, &((struct connection *) c)->fd, len);
    buf[len] = '\0';

    return buf;
}
