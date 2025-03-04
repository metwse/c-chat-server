#include "../../include/net/socket.h"
#include "../../include/net/connection.h"

#include <pthread.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#ifdef DEBUG
const struct tracing *t_connection;
#endif


void handle_socket(int socketfd) 
{
#ifdef DEBUG
TRACING(t_connection);
#endif
    unsigned int len = sizeof(struct sockaddr_in);
    pthread_attr_t attr;

    if (pthread_attr_init(&attr))
        return;

    while (1) {
        struct sockaddr_in *cli = malloc(len);

        int connfd = accept(socketfd, (struct sockaddr *) cli, &len);

        if (!connfd)
            continue;

#ifdef DEBUG
    LOG(t_connection, "new connetion with fd %d (port %d)", connfd, cli->sin_port)
#endif

        pthread_t *thread_id = malloc(sizeof(pthread_t));
        struct connection_info *cinfo = malloc(sizeof(struct connection_info));
        cinfo->sockaddr_in = cli;
        cinfo->connection_fd = connfd;

        pthread_create(thread_id, &attr, *handle_connection, cinfo);
    }

    close(socketfd);
}
