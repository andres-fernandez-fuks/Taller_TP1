//
// Created by andres on 8/10/20.
//

#include "common_socket_aux.h"
#ifndef AI_PASSIVE
#define AI_PASSIVE 1
#endif


void clientInitializeHints(struct addrinfo* hints);
void iterateAddressesForConnecting(struct addrinfo* results, struct addrinfo**
  address_dir, int* socket_fd);

void serverInitializeHints(struct addrinfo* hints);
void iterateAddressesForBinding(struct addrinfo* results, struct addrinfo**
address_dir, int* socket_fd);
int getaddrinfo(const char *node, const char *service, const struct addrinfo
*hints, struct addrinfo **res);
void freeaddrinfo(struct addrinfo *res);
int listenAndAccept(int socket_fd , struct addrinfo* address, int* accpt_sckt);


int connectToSocket(char* host_name, char* port_name, int* socket_fd) {
    struct addrinfo hints, *results, *address;
    int search;
    clientInitializeHints(&hints);
    search = getaddrinfo(host_name, port_name, &hints, &results);
    if (search != 0)
        return 1;
    iterateAddressesForConnecting(results, &address, socket_fd);
    if (!address)
        return 1;
    return 0;
}

void clientInitializeHints(struct addrinfo* hints) {
    memset(hints,0,sizeof(struct addrinfo));
    hints->ai_family = AF_INET;
    hints->ai_socktype = SOCK_STREAM;
    hints->ai_flags = 0;
}

void iterateAddressesForConnecting(struct addrinfo* results, struct addrinfo**
  address_dir, int* socket_fd) {
    struct addrinfo* address;
    for (address = results; address != NULL; address = address->ai_next) {
        *socket_fd = socket(address->ai_family, address->ai_socktype,
          address->ai_protocol);
        if (*socket_fd == -1)
            continue;

        if (connect(*socket_fd, address->ai_addr, address->ai_addrlen) != -1) {
            *address_dir = address;
            break;
        }
    }
    freeaddrinfo(results);
}

int sendMessage(int socket_fd, unsigned char* message, size_t len) {
    size_t contador = 0;
    while (contador < len) {
        int bytes_written = send(socket_fd, &message[contador], len-contador,
            0);
        if (bytes_written < 0)
            return 1;
        contador += bytes_written;
    }
    return 0;
}

int bindToSocket(struct addrinfo* addrinfo, int* connct_sckt, int*
accpt_sckt, char* port_name) {
    struct addrinfo hints, *results, *address;
    int socket_fd, search;
    serverInitializeHints(&hints);
    search = getaddrinfo(NULL, port_name, &hints, &results);
    if (search != 0)
        return 1;
    iterateAddressesForBinding(results, &address, &socket_fd);
    if (!address)
        return 1;
    *connct_sckt = socket_fd;
    memcpy(addrinfo, address, sizeof(struct addrinfo));
    int val_accept = listenAndAccept(socket_fd, address, accpt_sckt);
    freeaddrinfo(address);
    if (val_accept < 0)
        return 1;
    return 0;
}

void serverInitializeHints(struct addrinfo* hints) {
    memset(hints,0,sizeof(struct addrinfo));
    hints->ai_family = AF_INET;
    hints->ai_socktype = SOCK_STREAM;
    hints->ai_flags = AI_PASSIVE;
    hints->ai_protocol = 0;
}

void iterateAddressesForBinding(struct addrinfo* results, struct addrinfo**
address_dir, int* socket_fd) {
    struct addrinfo* address;
    for (address = results; address != NULL; address = address->ai_next) {
        *socket_fd = socket(address->ai_family, address->ai_socktype,
                            address->ai_protocol);
        if (*socket_fd == -1)
            continue;
        if (bind(*socket_fd, address->ai_addr, address->ai_addrlen) != -1) {
            *address_dir = address;
            break;
        }
    }
}

size_t receiveMessage(int peer_socket, unsigned char*
buffer) {
    if (peer_socket <0)
        return 1;
    size_t contador = 0;
    while (contador < 64) {
        int bytes_recv = recv(peer_socket, &buffer[contador], 64-contador, 0);
        if (bytes_recv < 0) {
            printf("Error: %s\n", strerror(errno));
            return 1;
        }
        contador += bytes_recv;
        if (bytes_recv == 0)
            break;
    }
    return contador;
}

int shutDownAndCloseSocket(int socket_fd) {
    if (shutdown(socket_fd,SHUT_RDWR) != 0)
        return 1;
    return close(socket_fd);
}

int listenAndAccept(int socket_fd , struct addrinfo* address, int* accpt_sckt) {
    if (listen(socket_fd,1) < 0)
        return 1;
    *accpt_sckt = accept(socket_fd, (struct sockaddr *)&address->ai_addr,
                         (socklen_t*) &address->ai_addrlen);
    int val = 1;
    setsockopt(*accpt_sckt, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));
    return *accpt_sckt;
}
