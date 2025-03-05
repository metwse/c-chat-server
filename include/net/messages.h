/*!
 * Handles messages of authenticated users.
 */

#ifndef NET_MESSAGES
#define NET_MESSAGES

#include "../database.h"
#include "../shared_state.h"

void handle_message(struct connection *, struct shared_state *, char *msg);

#endif
