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

typedef struct Socket{
    struct addrinfo* addr_info;
    int socket_fd;
} socket_t;
/*
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
*/
int socketInit(socket_t* self);
int socketConnect(socket_t* self, char* host_name, char* port_name);
int socketSendMessage(socket_t* self, unsigned char* message, size_t len);
int socketBind(socket_t* self, char* port_name);
size_t socketReceiveMessage(socket_t* self, unsigned char* buffer);
int socketClose(socket_t* self);
int socketAcceptConnection(socket_t* connection_sckt, socket_t* accept_sckt);

#endif //TP_1_COMMON_SOCKET_H
