/*!
 * Serves the chat server.
 */

#ifndef NET_SERVER
#define NET_SERVER

#include "../shared_state.h"

void serve(char *host, int port, struct shared_state *shared_state);

#endif
