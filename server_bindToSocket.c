//
// Created by andres on 8/10/20.
//

#include <stdlib.h>
#include <netdb.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <limits.h>

void serverInitializeHints(struct addrinfo* hints);
void iterateAddressesForBinding(struct addrinfo* results, struct addrinfo** address_dir, int* socket_fd);
size_t receiveMessageAndClose(struct addrinfo* address, int socket_fd, unsigned char* buffer);

size_t bindToSocket(char* port_name, unsigned char* buffer) {
    struct addrinfo hints, *results, *address;
    int socket_fd, search, iteration;
    serverInitializeHints(&hints);
    search = getaddrinfo(NULL, port_name, &hints, &results);
    if (search != 0)
        return 0; // en esta funcion, 0 indica error
    iterateAddressesForBinding(results, &address, &socket_fd);
    if (iteration != 0)
        return 0; // en esta funcion, 0 indica error
    return receiveMessageAndClose(address, socket_fd, buffer);
}

void serverInitializeHints(struct addrinfo* hints) {
    memset(hints,0,sizeof(struct addrinfo));
    hints->ai_family = AF_INET;
    hints->ai_socktype = SOCK_STREAM;
    hints->ai_flags = AI_PASSIVE;
    hints->ai_protocol = 0;
}

void iterateAddressesForBinding(struct addrinfo* results, struct addrinfo** address_dir, int* socket_fd) {
    struct addrinfo* address;
    for (address = results; address != NULL; address = address->ai_next) {
        *socket_fd = socket(address->ai_family, address->ai_socktype,address->ai_protocol);
        if (*socket_fd == -1)
            continue;
        if (bind(*socket_fd, address->ai_addr, address->ai_addrlen) != -1) {
            puts("Bindeado al socket!");
            *address_dir = address;
            break;
        }
    }
    freeaddrinfo(results);
}

size_t receiveMessageAndClose(struct addrinfo* address, int socket_fd, unsigned char* buffer) {
    if (listen(socket_fd,1) < 0)
        return 0; // en esta funcion, 0 indica error
    int peer_socket = accept(socket_fd, (struct sockaddr *)&address->ai_addr,
                                           (socklen_t*)&address->ai_addrlen);
    if (peer_socket <0)
        return 0; // en esta funcion, 0 indica error
    puts("Recibiendo mensaje...");
    size_t bytes_recv = recv(peer_socket, buffer, PATH_MAX, 0);
    close(peer_socket);
    return bytes_recv;
}