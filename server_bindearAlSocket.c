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

void inicializar_hints_server(struct addrinfo* hints);

int bindearAlSocket(char* port_name, unsigned char* buffer, size_t* bytes_recv) {
    struct addrinfo hints;
    struct addrinfo *results, *address;
    int socket_fd, s,peer_socket,valread;
    inicializar_hints_server(&hints);
    char *hello = "Hello from server";


    s = getaddrinfo(NULL, port_name, &hints, &results);
    if (s != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
        exit(EXIT_FAILURE);
    }

    for (address = results; address != NULL; address = address->ai_next) { // recorro la lista de ips obtenidas en results
        socket_fd = socket(address->ai_family, address->ai_socktype,0);
        if (socket_fd == -1)
            continue;

        if (bind(socket_fd, address->ai_addr, address->ai_addrlen) == 0)
            puts("Socket bindeado!");
            break;

        close(socket_fd);
    }

    if (!address) {       // no se puedo conectar
        fprintf(stderr, "Error en el bind\n");
        exit(EXIT_FAILURE);
    }

    if (listen(socket_fd,1) < 0) {
        fprintf(stderr,"Error en el listen\n");
        exit(EXIT_FAILURE);
    }

    if ((peer_socket = accept(socket_fd, (struct sockaddr *)&address->ai_addr,
            (socklen_t*)&address->ai_addrlen)) <0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    puts("Recibiendo mensaje...");
    *bytes_recv = recv(peer_socket, buffer, PATH_MAX, 0);
    freeaddrinfo(results);
    return 0;
}

void inicializar_hints_server(struct addrinfo* hints) {
    memset(hints,0,sizeof(struct addrinfo));
    hints->ai_family = AF_INET;
    hints->ai_socktype = SOCK_STREAM;
    hints->ai_flags = AI_PASSIVE;
    hints->ai_protocol = 0;
}