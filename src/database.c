#include "../include/database.h"

#include <stdlib.h>
#include <string.h>


const char *user_identify(const void *u) 
{
    return ((struct user *) u)->username;
}

const char *channel_identify(const void *c) 
{
    return ((struct channel *) c)->channel_name;
}

const char *connection_identify(const void *c) 
{
    unsigned len = sizeof(int) / sizeof(char);
    char *buf = malloc(len + 1);
    memcpy(buf, &((struct connection *) c)->fd, len);
    buf[len] = '\0';

    return buf;
}
