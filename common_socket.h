//
// Created by andres on 18/10/20.
//

#ifndef TP_1_COMMON_SOCKET_H
#define TP_1_COMMON_SOCKET_H

#include <stddef.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

typedef int (*connection_callback_t)(int sockfd, const struct sockaddr *addr,
        socklen_t addrlen);

struct addrinfo {
    int              ai_flags;
    int              ai_family;
    int              ai_socktype;
    int              ai_protocol;
    socklen_t        ai_addrlen;
    struct sockaddr *ai_addr;
    char            *ai_canonname;
    struct addrinfo *ai_next;
};

typedef struct Socket{
    struct addrinfo* connection_info;
    struct addrinfo* results;
    struct addrinfo hints;
    int socket_fd;
    connection_callback_t connection_callback;
    int connection_type;
} socket_t;


int getaddrinfo(const char *node, const char *service,
               const struct addrinfo *hints, struct addrinfo **res);

void freeaddrinfo(struct addrinfo *res);

int socketInit(socket_t* self, int connection_type);
int socketSendMessage(socket_t* self, unsigned char* message, size_t len);
int socketConnect(socket_t* self, char* host_name, char* port_name);
int socketReceiveMessage(socket_t* self, unsigned char* buffer);
int socketClose(socket_t* self);
int socketAcceptConnection(socket_t* connection_sckt, socket_t* accept_sckt);

#endif //TP_1_COMMON_SOCKET_H
