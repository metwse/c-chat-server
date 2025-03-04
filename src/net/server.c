#include "../../include/net/server.h" 
#include "../../include/net/socket.h" 

#include <netinet/in.h>
#include <stdio.h>
#include <strings.h>
#include <unistd.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <stdio.h>
#include <arpa/inet.h>

#define EXIT(EXIT_CODE, ...) do { \
        if (sizeof((char[]) { #__VA_ARGS__ })) \
            fprintf(stderr, __VA_ARGS__); \
        exit(EXIT_CODE); \
    } while (0);

#ifdef DEBUG
const struct tracing *t_server;
#endif


void serve(char *host, int port, void *shared_state) 
{
#ifdef DEBUG
TRACING(t_server);
SPAN(t_server, init);
#endif

    struct sockaddr_in servaddr;
    struct in_addr inaddr;

    if (!inet_aton(host, &inaddr))
        EXIT(1, "Invalid hostname");

    servaddr.sin_addr = inaddr;
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(port);

    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd == -1) 
        EXIT(1, "Socket creation failed");

#ifdef DEBUG
LOG(init, "socket created with fd %d", socketfd);
#endif

    if (bind(socketfd, (struct sockaddr *) &servaddr, sizeof(servaddr)))
        EXIT(1, "Cannot bind the sockaddr");

#ifdef DEBUG
LOG(init, "socket binded");
#endif

    if (listen(socketfd, 5))
        EXIT(1, "Listen failed");

#ifdef DEBUG
LOG(init, "listening port");
#endif

    handle_socket(socketfd, shared_state);
}
