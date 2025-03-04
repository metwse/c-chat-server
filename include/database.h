/*!
 * User/connection related structs/collectables.
 */

#ifndef DATABASE
#define DATABASE

#include "collections/linked_list.h"

/**
 * User struct.
 */
struct user {
    char *username;
    char *password;
    struct linked_list connections;
};

/**
 * Channel struct.
 */
struct channel {
    char *channel_name;
    char *password;
};

/**
 * Connection struct.
 *
 * Authenticated connections are stored in this type.
 */
struct connection {
    int fd;
    struct user *user;
};

const char *user_identify(void const *);
int user_ordering(void const *, void const *);

const char *channel_identify(void const *);
int channel_ordering(void const *, void const *);

const char *connection_identify(void const *);

#endif
