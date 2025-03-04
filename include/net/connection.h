/*!
 * Handles connections.
 */

#ifndef NET_CONNECTION
#define NET_CONNECTION

#include <netinet/in.h>

struct connection_info {
    int connection_fd;
    struct sockaddr_in *sockaddr_in;
};

void *handle_connection(void *);

#endif

