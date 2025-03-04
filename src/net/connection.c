#include "../../include/net/connection.h"

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <strings.h>
#include <stdio.h>
#include <stdbool.h>

#define SAVE_BUF(var) do { \
        var = malloc((readen + 1) * sizeof(char)); \
        strncat(var, buf, readen); \
        var[readen] = '\0'; \
    } while (0)

#define PRINT(fd, ...) dprintf(fd, __VA_ARGS__);

static const char *WELCOME_MESSAGE = "Welcome to the chat server!\nusername: ";


void *handle_connection(void *connection_info) 
{
    struct connection_info *cinfo = connection_info;
    int fd = cinfo->connection_fd;
    struct sockaddr_in *cli = cinfo->sockaddr_in;
    struct shared_state *ss = cinfo->shared_state;

    PRINT(fd, "%s", WELCOME_MESSAGE);

    char *buf = malloc(sizeof(char) * 2048);
    bzero(buf, 2047);

    int readen = 0;
    bool is_authenticated = false;
    bool credentials_given = false;

    char *username = NULL;
    char *password = NULL;
    char accept_account_creation = '\0';

    while (1) {
        readen = read(fd, buf, 2048);

        if (readen == -1 || readen == 2048 || !readen)
            break;

        if (readen >= 2) {
            readen -= 2;
            buf[readen] = 0;
        } else 
            break;

        if (!is_authenticated) {
            if (!credentials_given) {
                if (!username && readen) {
                    SAVE_BUF(username);
                    PRINT(fd, "password: ");
                } else if (!username) {
                    PRINT(fd, "username: ");
                } else if (!password && readen) {
                    SAVE_BUF(password);
                    PRINT(fd,
                          "User %s not found. Would you like to create a new "
                          "account? (y/n): ", username);
                    credentials_given = true;
                } else {
                    PRINT(fd, "password: ");
                }
            } else {
                accept_account_creation = buf[0];
                struct user *u = bstree_get(ss->users, username);

                if (u) {
                    // TODO: is_authenticated
                } else if (
                    accept_account_creation != 'n' &&
                    accept_account_creation != 'y'
                ) {
                    PRINT(fd, "(y/n): ");
                } else {
                    break;
                }
            }
        } else {
            // TODO
        }

        bzero(buf, readen + 2);
    }

    free(cli);
    free(buf);
    free(connection_info);
    close(fd);

    return NULL;
}
