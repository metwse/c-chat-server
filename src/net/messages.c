#include "../../include/collections/linked_list.h"
#include "../../include/net/messages.h"
#include "../../include/database.h"
#include "../../include/shared_state.h"
#include <pthread.h>
#include <string.h>
#include <stddef.h>
#include <stdio.h>

#define LOCK pthread_mutex_lock(&ss->lock);
#define UNLOCK pthread_mutex_unlock(&ss->lock);


void handle_message(struct connection *conn, struct shared_state *ss,
                    char *msg) {
    switch (msg[0]) {
        case '/':
            LOCK;
            int fd = conn->fd;
            char *rest = msg;
            char *command = strtok_r(rest, " ", &rest);

            // TODO: commands
            if (!strcmp(command, "/subscribe")) {
                UNLOCK;
            } else if (!strcmp(command, "/unsubscribe")) {
                UNLOCK;
            } else if (!strcmp(command, "/list_users")) {
                UNLOCK;
            } else if (!strcmp(command, "/delete")) {
                UNLOCK;
            } else if (!strcmp(command, "/logout")) {
                UNLOCK;
            } else {
                UNLOCK;
                dprintf(fd, "Unknown command!\n");
            }

            break;
        case '#':
            // TODO: send to a channel
            UNLOCK;
            break;
        case '@':
            // TODO: send to a user
            UNLOCK;
            break;
        default:
            LOCK;
            struct linked_list *fds = linked_list_new(NULL, NULL);
            struct linked_list *channels = linked_list_new(NULL, NULL);
            char *username = strdup(conn->user->username);

            if (!conn->user->channels->length) {
                int fd = conn->fd;
                UNLOCK;
                dprintf(fd, "You are not in any channel. Consider using "
                        "/subscribe <channel_name> <channel_password> to "
                        "create or join a channel.\n");
                break;
            }

            // TODO: linked_list_clone
            for (size_t i = 0; i < conn->user->channels->length; i++) {
                linked_list_push(channels,
                                 linked_list_get(conn->user->channels, i));
            }
            // TODO: linked_list_iter
            for (size_t i = 0; i < channels->length; i++) {
                struct connection *c = linked_list_get(channels, i);
                if (strcmp(c->user->username, conn->user->username))
                    linked_list_push(fds, &c->fd);
            }
            linked_list_drop(channels);
            UNLOCK;

            for (size_t i = 0; i < fds->length; i++) {
                int fd = *(int *) linked_list_get(fds, i);
                // TODO: multithreaded send
                dprintf(fd, "@%s: %s\n", username, msg);
            }
            linked_list_drop(fds);

            break;
    }
}
