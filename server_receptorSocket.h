//
// Created by andres on 12/10/20.
//

#ifndef TP_1_SERVER_RECEPTORSOCKET_H
#define TP_1_SERVER_RECEPTORSOCKET_H

#include <stddef.h>
#include "common_aux_socket.h"

typedef struct receptorSocket{
    struct addrinfo* addr_info;
    int connection_socket_fd;
    int acceptance_socket_fd;
} rSocket_t;

int receptorSocketInit(rSocket_t* self);
int socketBind(rSocket_t* self, char* port_name);
size_t socketReceiveMessage(rSocket_t* self, unsigned char* buffer);
int receptorSocketClose(rSocket_t* self);

#endif //TP_1_SERVER_RECEPTORSOCKET_H
