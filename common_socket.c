//
// Created by andres on 18/10/20.
//

#include "common_socket.h"

#define CHUNK_SIZE 64

void iterateAddressesForConnecting(struct addrinfo* results, struct addrinfo**
address_dir, int* socket_fd, connection_callback_t function);
int connectToSocket(char* host_name, char* port_name, int* socket_fd);
int shutDownAndCloseSocket(int socket_fd);

int socketInit(socket_t* self) {
    self-> addr_info = malloc(sizeof(struct addrinfo));
    self-> socket_fd = 0;
    return 0;
}

int socketClose(socket_t* self) {
    if (shutdown(self->socket_fd,SHUT_RDWR) != 0)
        return 1;
    free(self->addr_info);
    return close(self->socket_fd);
}

void initializeHints(struct addrinfo* hints, int ai_flags) {
    memset(hints,0,sizeof(struct addrinfo));
    hints->ai_family = AF_INET;
    hints->ai_socktype = SOCK_STREAM;
    hints->ai_flags = ai_flags;
    if (ai_flags != 0)
        hints->ai_protocol = 0;
}

int socketConnect(socket_t* self, char* host_name, char* port_name) {
    struct addrinfo hints, *results, *address;
    int search;
    initializeHints(&hints, 0);
    search = getaddrinfo(host_name, port_name, &hints, &results);
    if (search != 0)
        return 1;
    iterateAddressesForConnecting(results, &address, &self->socket_fd,
                                  &connect);
    if (!address)
        return 1;
    freeaddrinfo(results);
    return 0;
}

int socketBind(socket_t* self, char* port_name) {
    struct addrinfo hints, *results, *address;
    int socket_fd, search;
    initializeHints(&hints, AI_PASSIVE);
    search = getaddrinfo(NULL, port_name, &hints, &results);
    if (search != 0)
        return 1;
    iterateAddressesForConnecting(results, &address, &socket_fd, &bind);
    if (!address)
        return 1;
    self->socket_fd = socket_fd;
    memcpy(self->addr_info, address, sizeof(struct addrinfo));
    freeaddrinfo(results);
    return 0;
}

void iterateAddressesForConnecting(struct addrinfo* results, struct addrinfo**
    address_dir, int* socket_fd, connection_callback_t function) {
    struct addrinfo* address;
    for (address = results; address != NULL; address = address->ai_next) {
        *socket_fd = socket(address->ai_family, address->ai_socktype,
                            address->ai_protocol);
        if (*socket_fd == -1)
            continue;

        if (function(*socket_fd, address->ai_addr, address->ai_addrlen) != -1) {
            *address_dir = address;
            break;
        }
    }
}

int socketAcceptConnection(socket_t* connection_sckt, socket_t* accept_sckt) {
    if (listen(connection_sckt->socket_fd, 1) < 0)
        return 1;

    accept_sckt->socket_fd = accept(connection_sckt->socket_fd, (struct sockaddr
            *)&connection_sckt->addr_info-> ai_addr,(socklen_t*)
            &connection_sckt->addr_info->ai_addrlen);
    int val = 1;
    setsockopt(accept_sckt->socket_fd, SOL_SOCKET, SO_REUSEADDR, &val,
               sizeof(val));
    return 0;
}

size_t socketReceiveMessage(socket_t* self, unsigned char* buffer) {
    if (self->socket_fd <0)
        return 1;
    size_t contador = 0;
    while (contador < CHUNK_SIZE) {
        int bytes_recv = recv(self->socket_fd, &buffer[contador],
                              CHUNK_SIZE-contador, 0);
        if (bytes_recv < 0) {
            return 1;
        }
        contador += bytes_recv;
        if (bytes_recv == 0)
            break;
    }
    return contador;
}

int socketSendMessage(socket_t* self, unsigned char* message, size_t len) {
    size_t contador = 0;
    while (contador < len) {
        int bytes_written = send(self->socket_fd, &message[contador],
                                 len-contador, MSG_NOSIGNAL);
        if (bytes_written < 0)
            return 1;
        contador += bytes_written;
    }
    return 0;
}



