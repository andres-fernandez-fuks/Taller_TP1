//
// Created by andres on 18/10/20.
//

#include "common_socket.h"
#include "common_socket_aux.h"

int socketInit(socket_t* self) {
    self-> addr_info = malloc(sizeof(struct addrinfo));
    self-> connection_socket_fd = 0;
    self-> acceptance_socket_fd = 0;
    return 0;
}

int socketConnect(socket_t* self, char* host_name, char* port_name) {
    return connectToSocket(host_name, port_name, &self->connection_socket_fd);
}

size_t socketSendMessage(socket_t* self, unsigned char* buffer, size_t len) {
    return sendMessage(self->connection_socket_fd, buffer, len);
}

int socketBind(socket_t* self, char* port_name) {
    return bindToSocket(self->addr_info, &self->connection_socket_fd,
                        &self->acceptance_socket_fd, port_name);
}

size_t socketReceiveMessage(socket_t* self, unsigned char* buffer) {
    return receiveMessage(self->acceptance_socket_fd, buffer);
}

int socketClose(socket_t* self) {
    if (shutDownAndCloseSocket(self->connection_socket_fd) < 0)
        return 1;
    if (self->acceptance_socket_fd) {
        if (shutDownAndCloseSocket(self->acceptance_socket_fd) < 0)
            return 1;
    }
    free(self->addr_info);
    return 0;
}

