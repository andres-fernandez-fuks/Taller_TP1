//
// Created by andres on 18/10/20.
//

#ifndef TP_1_COMMON_SOCKET_H
#define TP_1_COMMON_SOCKET_H

#include <stddef.h>

typedef struct Socket{
    struct addrinfo* addr_info;
    int connection_socket_fd;
    int acceptance_socket_fd;
} socket_t;

int socketInit(socket_t* self);
int socketConnect(socket_t* self, char* host_name, char* port_name);
size_t socketSendMessage(socket_t* self, unsigned char* buffer, size_t len);
int socketBind(socket_t* self, char* port_name);
size_t socketReceiveMessage(socket_t* self, unsigned char* buffer);
int socketClose(socket_t* self);

#endif //TP_1_COMMON_SOCKET_H
