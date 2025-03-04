#include "../../include/net/connection.h"

#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <strings.h>
#include <stdio.h>


void *handle_connection(void *connection_info) 
{
    struct connection_info *cinfo = connection_info;
    int connfd = cinfo->connection_fd;
    struct sockaddr_in *cli = cinfo->sockaddr_in;

    while (1) {
        char *buf = malloc(sizeof(char) * 2048);
        bzero(buf, 2047);

        if (read(connfd, buf, 2047) == -1)
            break;

        printf("%s", buf);
    }
    free(cli);
    free(connection_info);
    close(connfd);

    return NULL;
}
