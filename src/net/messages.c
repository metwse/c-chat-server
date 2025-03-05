#include "../../include/collections/linked_list.h"
#include "../../include/net/messages.h"
#include "../../include/database.h"
#include "../../include/shared_state.h"
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdio.h>

#define LOCK pthread_mutex_lock(&ss->lock);
#define UNLOCK pthread_mutex_unlock(&ss->lock);
#define NEXT_TOKEN(var) char *var = strtok_r(rest, " ", &rest);


enum cmd_data_type {
    CREATE_CHANNEL,
};

struct cmd_data {
    enum cmd_data_type type;
    void **data;
};


void handle_message(struct connection *conn, struct shared_state *ss,
                    char *msg) {
    LOCK;
    int fd = conn->fd;

    if (conn->cmd_data) {
        struct cmd_data *data = conn->cmd_data;
        conn->cmd_data = NULL;

        switch (data->type) {
            case CREATE_CHANNEL:
                switch (msg[0]) {
                    case 'y':
                        if (bstree_contains(ss->channels, data->data[0])) {
                            UNLOCK;
                            dprintf(fd, "> Unexpected error! Pleaase try"
                                    " again.\n");
                            break;
                        }
                        struct channel *c = malloc(sizeof(struct channel));
                        c->channel_name = data->data[0];
                        c->password = data->data[1];
                        c->users = linked_list_new(user_identify, NULL);
                        linked_list_push(c->users, conn->user);
                        linked_list_push(conn->user->channels, c);
                        bstree_push(ss->channels, c);
                        UNLOCK;
                        dprintf(fd, "> Channel created.\n");
                        break;
                    default:
                        UNLOCK;
                        dprintf(fd, "> Abort\n");
                        free(data->data[0]);
                        free(data->data[1]);
                        break;
                }
                break;
        }

        free(data);
        return;
    }
    
    struct linked_list *fds;
    char *username;
    char *rest = msg;

    switch (msg[0]) {
        case '/':;
            char *command = strtok_r(rest, " ", &rest);

            if (!strcmp(command, "/subscribe")) {
                NEXT_TOKEN(channel_name);
                if (channel_name) {
                    NEXT_TOKEN(channel_password);
                    if (channel_password) {
                        struct channel *c = bstree_get(ss->channels,
                                                       channel_name);
                        if (!c) {
                            struct cmd_data *data = \
                                malloc(sizeof(struct cmd_data));
                            data->type = CREATE_CHANNEL;
                            data->data = calloc(sizeof(char *), 2);
                            data->data[0] = strdup(channel_name);
                            data->data[1] = strdup(channel_password);
                            conn->cmd_data = data;

                            UNLOCK;
                            dprintf(fd, "> Channel %s not found. Would you "
                                    "like to create a new channel? (y/n): ",
                                    channel_name);
                        } else {
                            if (!strcmp(c->password, channel_password)) {
                                linked_list_push(c->users, conn->user);
                                linked_list_push(conn->user->channels, c);
                                UNLOCK;
                                dprintf(fd, "> Joined #%s\n", channel_name);
                            } else {
                                UNLOCK;
                                dprintf(fd, "> Invalid password!\n");
                            }
                        }
                        break;
                    }
                }
                UNLOCK;
                dprintf(fd, "> Syntax error. Usage: /subscribe <channel_name> "
                        "<channel_password>\n");
            } else if (!strcmp(command, "/unsubscribe")) {
                dprintf(fd, "> Not implemented yet!\n");
                UNLOCK;
            } else if (!strcmp(command, "/list_users")) {
                dprintf(fd, "> Not implemented yet!\n");
                UNLOCK;
            } else if (!strcmp(command, "/delete")) {
                dprintf(fd, "> Not implemented yet!\n");
                UNLOCK;
            } else if (!strcmp(command, "/logout")) {
                dprintf(fd, "> Not implemented yet!\n");
                UNLOCK;
            } else {
                UNLOCK;
                dprintf(fd, "> Unknown command!\n");
            }

            break;
        case '#':;
            fds = linked_list_new(NULL, NULL);
            username = strdup(conn->user->username);

            char *channel = strtok_r(rest, " ", &rest) + 1;
            if (strlen(channel) < 2) {
                UNLOCK;
                break;
            }
            struct channel *c = bstree_get(ss->channels, channel);
            if (!c) {
                UNLOCK;
                dprintf(fd, "> Cannot find channel %s.\n", channel);
                break;
            }

            bool can_send = false;

            for (size_t j = 0; j < c->users->length; j++) {
                struct user *u = linked_list_get(c->users, j);
                if (strcmp(username, u->username))
                    for (size_t k = 0; k < u->connections->length; k++) {
                        struct connection *con = linked_list_get(u->connections, k);
                        linked_list_push(fds, &con->fd);
                    }
                else 
                    can_send = true;
            }
            UNLOCK;

            if (can_send)
                for (size_t i = 0; i < fds->length; i++) {
                    int fd = *(int *) linked_list_get(fds, i);
                    // TODO: multithreaded send
                    dprintf(fd, "[#%s @%s]: %s\n", channel, username, rest);
                }
            else 
                dprintf(fd, "> Cannot acces to the channel.");
            linked_list_drop(fds);
            free(username);

            break;
        case '@':
            fds = linked_list_new(NULL, NULL);
            username = strdup(conn->user->username);

            char *username_ = strtok_r(rest, " ", &rest) + 1;
            if (strlen(username_) < 2 || !strcmp(username, username_)) {
                UNLOCK;
                break;
            }

            struct user *u = bstree_get(ss->users, username_);
            if (!u) {
                UNLOCK;
                dprintf(fd, "> Cannot find user %s.\n", username_);
                break;
            }

            for (size_t k = 0; k < u->connections->length; k++) {
                struct connection *con = linked_list_get(u->connections, k);
                linked_list_push(fds, &con->fd);
            }
            UNLOCK;

            for (size_t i = 0; i < fds->length; i++) {
                int fd = *(int *) linked_list_get(fds, i);
                // TODO: multithreaded send
                dprintf(fd, "[dm @%s]: %s\n", username, rest);
            }
            linked_list_drop(fds);
            free(username);

            break;
        default:;
            fds = linked_list_new(NULL, NULL);
            username = strdup(conn->user->username);

            if (!conn->user->channels->length) {
                UNLOCK;
                dprintf(fd, "> You are not in any channel. Consider using "
                        "/subscribe <channel_name> <channel_password> to "
                        "create or join a channel.\n");
                break;
            }

            // TODO: linked_list_clone
            for (size_t i = 0; i < conn->user->channels->length; i++) {
                struct channel *c = linked_list_get(conn->user->channels, i);
                for (size_t j = 0; j < c->users->length; j++) {
                    struct user *u = linked_list_get(c->users, j);
                    if (strcmp(username, u->username))
                        for (size_t k = 0; k < u->connections->length; k++) {
                            struct connection *con = linked_list_get(u->connections, k);
                            linked_list_push(fds, &con->fd);
                        }
                }
            }
            UNLOCK;

            for (size_t i = 0; i < fds->length; i++) {
                int fd = *(int *) linked_list_get(fds, i);
                // TODO: multithreaded send
                dprintf(fd, "@%s: %s\n", username, msg);
            }
            linked_list_drop(fds);
            free(username);

            break;
    }
}
