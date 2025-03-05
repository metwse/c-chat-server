/*!
 * User/connection related structs/collectables.
 */

#ifndef DATABASE
#define DATABASE

#include "collections/linked_list.h"
#include <stdbool.h>


/**
 * User struct.
 */
struct user {
    char *username;
    char *password;
    struct linked_list *connections;
    struct linked_list *channels;
};

/**
 * Channel struct.
 */
struct channel {
    char *channel_name;
    char *password;
    struct linked_list *users;
};

/**
 * Connection struct.
 *
 * Authenticated connections are stored in this type.
 */
struct connection {
    int fd;
    bool drop;
    struct user *user;
};

const char *user_identify(void const *);
int user_ordering(void const *, void const *);

const char *channel_identify(void const *);
int channel_ordering(void const *, void const *);

const char *connection_identify(void const *);

#endif
