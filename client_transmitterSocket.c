//
// Created by andres on 12/10/20.
//

#include "client_transmitterSocket.h"
#include "common_aux_socket.h"

int transmissionSocketInit(tSocket_t* self) {
    self->addr_info = malloc(sizeof(struct addrinfo));
    self->socket_fd = 0;
    return 0;
}
int socketConnect(tSocket_t* self, char* host_name, char* port_name) {
    return connectToSocket(host_name, port_name, &self->socket_fd);
}
size_t socketSendMessage(tSocket_t* self, unsigned char* buffer, size_t len) {
    return sendMessage(self->socket_fd, buffer, len);
}
int transmissionSocketClose(tSocket_t* self) {
    shutdownAndClose(self->socket_fd);
    free(self->addr_info);
    return 0;
}
