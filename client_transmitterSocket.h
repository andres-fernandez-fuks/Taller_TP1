//
// Created by andres on 12/10/20.
//

#ifndef TP_1_CLIENT_TRANSMITTERSOCKET_H
#define TP_1_CLIENT_TRANSMITTERSOCKET_H

#include <stddef.h>
#include "common_aux_socket.h"

typedef struct transmitterSocket{
    struct addrinfo* addr_info;
    int socket_fd;
} tSocket_t;

int transmissionSocketInit(tSocket_t* self);
int socketConnect(tSocket_t* self, char* host_name, char* port_name);
size_t socketSendMessage(tSocket_t* self, unsigned char* buffer, size_t len);
int transmissionSocketClose(tSocket_t* self);


#endif //TP_1_CLIENT_TRANSMITTERSOCKET_H
