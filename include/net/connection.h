/*!
 * Handles connections.
 */

#ifndef NET_CONNECTION
#define NET_CONNECTION

#include <netinet/in.h>
#include "../shared_state.h"

struct connection_info {
    int connection_fd;
    struct sockaddr_in *sockaddr_in;
    struct shared_state *shared_state;
};

void *handle_connection(void *);

#endif

