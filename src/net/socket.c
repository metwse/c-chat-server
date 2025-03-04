#include "../../include/net/socket.h"

#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <strings.h>
#include <stdio.h>


void handle_socket(int socketfd) {
#ifdef DEBUG
SPAN(t_server, connection);
#endif
    
    unsigned int len = sizeof(struct sockaddr_in);
    struct sockaddr_in *cli = malloc(len);

    int connfd = accept(socketfd, (struct sockaddr *) cli, &len);

    if (!connfd)
        return;

#ifdef DEBUG
LOG(connection, "new connetion with fd %d (port %d)", connfd, cli->sin_port)
#endif

    // TODO: implement command handling
    char buf[80];
    bzero(&buf, 80);

    read(connfd, buf, 80);
    printf("%s", buf);

    close(connfd);
    return;
}

