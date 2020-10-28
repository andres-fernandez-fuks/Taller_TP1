//
// Created by andres on 18/10/20.
//

#include "common_socket.h"

#ifndef AI_PASSIVE
#define AI_PASSIVE 1
#endif

#define CHUNK_SIZE 64
#define CONNECT_TYPE 0
#define BIND_TYPE 1

void socketSetConnectionCallback(socket_t* self, int connection_type) {
    switch (connection_type) {
        case CONNECT_TYPE:
            self->connection_callback = &connect;
            break;
        case BIND_TYPE:
            self->connection_callback = &bind;
            break;
    }
}

int socketInit(socket_t* self, int connection_type) {
    memset(&self->hints, 0, sizeof(struct addrinfo));
    self-> socket_fd = 0;
    self->connection_type = connection_type;
    socketSetConnectionCallback(self, connection_type);
    return 0;
}

int socketClose(socket_t* self) {
    if (!self)
        return 1;
    if (shutdown(self->socket_fd,SHUT_RDWR) != 0)
        return 1;
    if (self->results)
        freeaddrinfo(self->results);
    return close(self->socket_fd);
}

void initializeHints(struct addrinfo* hints, int ai_flags) {
    memset(hints,0,sizeof(struct addrinfo));
    hints->ai_family = AF_INET;
    hints->ai_socktype = SOCK_STREAM;
    hints->ai_flags = ai_flags;
}

void setBindingOptions(int connection_type, int socket_fd) {
    if (connection_type == CONNECT_TYPE)
        return;
    int val = 1;
    setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));
}

void socketIterateAddressesForConnecting(socket_t* self) {
    struct addrinfo* address;
    setBindingOptions(self->connection_type, self->socket_fd);
    for (address = self->results; address != NULL; address = address->ai_next) {
        self->socket_fd = socket(address->ai_family, address->ai_socktype,
                            address->ai_protocol);
        if (self->socket_fd == -1)
            continue;
        if (self->connection_callback(self->socket_fd, address->ai_addr,
                                      address->ai_addrlen) != -1) {
            self->connection_info = address;
            break;
        }
    }
}

int socketConnect(socket_t* self, char* host_name, char* port_name) {
    int search;
    initializeHints(&self->hints, AI_PASSIVE);
    search = getaddrinfo(host_name, port_name, &self->hints, &self->results);
    if (search != 0)
        return 1;
    socketIterateAddressesForConnecting(self);
    if (!self->connection_info)
        return 1;
    return 0;
}

int socketAcceptConnection(socket_t* connection_sckt, socket_t* accept_sckt) {
    if (listen(connection_sckt->socket_fd, 1) < 0)
        return 1;

    int val_accept = accept_sckt->socket_fd = accept(connection_sckt->socket_fd,
             (struct sockaddr*)&connection_sckt->connection_info-> ai_addr,
              (socklen_t*) &connection_sckt->connection_info->ai_addrlen);
    if (val_accept < 0)
        return 1;
    return 0;
}

int socketReceiveMessage(socket_t* self, unsigned char* buffer) {
    if (self->socket_fd <0)
        return 1;
    size_t counter = 0;
    while (counter < CHUNK_SIZE) {
        int bytes_recv = recv(self->socket_fd, &buffer[counter],
                              CHUNK_SIZE-counter, 0);
        if (bytes_recv < 0) {
            return -1;
        }
        counter += bytes_recv;
        if (bytes_recv == 0)
            break;
    }
    return counter;
}

int socketSendMessage(socket_t* self, unsigned char* message, size_t len) {
    size_t counter = 0;
    while (counter < len) {
        int bytes_written = send(self->socket_fd, &message[counter],
                                 len-counter, MSG_NOSIGNAL);
        if (bytes_written < 0)
            return 1;
        counter += bytes_written;
    }
    return 0;
}



