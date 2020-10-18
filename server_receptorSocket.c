//
// Created by andres on 12/10/20.
//

#include "server_receptorSocket.h"

int receptorSocketInit(rSocket_t* self) {
    self-> addr_info = malloc(sizeof(struct addrinfo));
    self-> connection_socket_fd = 0;
    self-> acceptance_socket_fd = 0;
    return 0;
}

int socketBind(rSocket_t* self, char* port_name) {
    return bindToSocket(self->addr_info, &self->connection_socket_fd,
                               &self->acceptance_socket_fd, port_name);
}

size_t socketReceiveMessage(rSocket_t* self, unsigned char* buffer) {
    return receiveMessage(self->acceptance_socket_fd, buffer);
}

int receptorSocketClose(rSocket_t* self) {
    if (closeSocket(self->connection_socket_fd) < 0)
        return 1;
    if (closeSocket(self->acceptance_socket_fd) < 0)
        return 1;
    free(self->addr_info);
    return 0;
}
