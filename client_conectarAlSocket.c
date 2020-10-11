//
// Created by andres on 8/10/20.
//

#include <stdlib.h>
#include <netdb.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

#include "common_aux_cipher.h"

void initializeHints(struct addrinfo* hints);
void iterateAddresses(struct addrinfo* results, struct addrinfo* address, int* socket_fd);
int sendMessageAndClose(int socket_fd, char* mensaje, size_t len);

int connectToSocket(unsigned char* mensaje, size_t len, char* host_name, char* port_name) {
    struct addrinfo hints;
    struct addrinfo *results, *address;
    int search, socket_fd;
    initializeHints(&hints);
    search = getaddrinfo(host_name, port_name, &hints, &results);
    if (search != 0)
        return 1;
    iterateAddresses(results, address,&socket_fd);
    if (!address)
        return 1;
    return sendMessageAndClose(socket_fd, mensaje, len);
}

void initializeHints(struct addrinfo* hints) {
    memset(hints,0,sizeof(struct addrinfo));
    hints->ai_family = AF_INET;
    hints->ai_socktype = SOCK_STREAM;
    hints->ai_flags = 0;
}

void iterateAddresses(struct addrinfo* results, struct addrinfo* address, int* socket_fd) {
    for (address = results; address != NULL; address = address->ai_next) {
        *socket_fd = socket(address->ai_family, address->ai_socktype,address->ai_protocol);
        if (*socket_fd == -1)
            continue;

        if (connect(*socket_fd, address->ai_addr, address->ai_addrlen) != -1) {
            puts("Conectado al socket!");
            break;
        }
    }
    freeaddrinfo(results);
}

int sendMessageAndClose(int socket_fd, char* mensaje, size_t len) {
    if (send(socket_fd,mensaje,len, 0) < 0)
        return 1;
    if (shutdown(socket_fd, SHUT_RDWR) < 0)
        return 1;
    if (close(socket_fd) < 0)
        return 1;
    return 0;
}