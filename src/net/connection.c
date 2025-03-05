#include "../../include/net/connection.h"
#include "../../include/net/messages.h"
#include "../../include/database.h"

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <strings.h>
#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>

#define SAVE_BUF(var) do { \
        var = malloc((readen + 1) * sizeof(char)); \
        strncpy(var, buf, readen); \
        var[readen] = '\0'; \
    } while (0)

#define PRINT(fd, ...) dprintf(fd, __VA_ARGS__)


void *handle_connection(void *_cinfo) 
{
    struct connection_info *cinfo = _cinfo;
    int fd = cinfo->connection_fd;
    struct sockaddr_in *cli = cinfo->sockaddr_in;
    struct shared_state *ss = cinfo->shared_state;

    struct connection *conn = malloc(sizeof(struct connection));
    conn->fd = fd;
    conn->user = NULL;
    conn->drop = false;
    conn->cmd_data = NULL;

    PRINT(fd, "Welcome to the chat server!\nusername: ");

    char *buf = malloc(sizeof(char) * 2048);
    bzero(buf, 2048);

    int readen = 0;
    bool is_authenticated = false;
    bool credentials_given = false;

    char *username = NULL;
    char *password = NULL;
    char accept_account_creation = '\0';

    while (1) {
        readen = read(fd, buf, 2048);
        if (conn->drop)
            break;

        if (readen == -1 || readen == 2048 || !readen)
            break;

        if (readen >= 2) {
            readen -= 2;
            buf[readen] = 0;
        } else 
            break;

        if (!is_authenticated) {
            accept_account_creation = buf[0];

            // ask for username and password
            if (!credentials_given) {
                if (!username && readen) {
                    SAVE_BUF(username);
                    PRINT(fd, "password: ");
                } else if (!username)
                    PRINT(fd, "username: ");
                else if (!password && readen) {
                    SAVE_BUF(password);
                    credentials_given = true;
                } else
                    PRINT(fd, "password: ");

                accept_account_creation = '\0';
            } 

            if (credentials_given) {
                pthread_mutex_lock(&ss->lock);
                struct user *u = bstree_get(ss->users, username);

                // check whether password is correct if user exits
                if (u) {
                    if (!strcmp(u->password, password)) {
                        is_authenticated = true;
                        conn->user = u;
                        linked_list_push(u->connections, conn);
                        pthread_mutex_unlock(&ss->lock);
                        PRINT(fd, "Welcome!\n");
                    } else {
                        pthread_mutex_unlock(&ss->lock);
                        password = NULL;
                        PRINT(fd, "Invalid password!\npassword: ");
                        credentials_given = false;
                    }
                } // ask for account creation if no such account exits
                else if (accept_account_creation == 'y') {
                    if (bstree_contains(ss->users, username)) {
                        pthread_mutex_unlock(&ss->lock);
                        PRINT(fd, 
                              "Unexcepted error! Please try again later.\n");
                        break;
                    }

                    u = malloc(sizeof(struct user));
                    conn->user = u;
                    u->username = username;
                    u->password = password;
                    u->connections = linked_list_new(connection_identify, NULL);
                    u->channels = linked_list_new(channel_identify, NULL);
                    linked_list_push(u->connections, conn);
                    bstree_push(ss->users, u);

                    is_authenticated = true;
                    pthread_mutex_unlock(&ss->lock);

                    PRINT(fd, "Account created. Welcome!\n");
                } else if (accept_account_creation == 'n') {
                    pthread_mutex_unlock(&ss->lock);
                    PRINT(fd, "Bye!\n");
                    break;
                } else if (!u) {
                    pthread_mutex_unlock(&ss->lock);
                    PRINT(fd,
                          "User %s not found. Would you like to create a new "
                          "account? (y/n): ", username);
                }
            }
        } else {
            handle_message(conn, ss, buf);
            
            if (conn->drop)
                break;
        }

        bzero(buf, readen + 2);
    }

    if (conn->user && conn->user->connections)
        linked_list_remove_by_id(conn->user->connections,
                                 connection_identify(conn));

    if (!is_authenticated) {
        if (username)
            free(username);
        if (password)
            free(password);
    }

    pthread_mutex_lock(&ss->lock);
    free(conn);
    free(cli);
    free(buf);
    free(cinfo);
    close(fd);
    pthread_mutex_unlock(&ss->lock);

    return NULL;
}
