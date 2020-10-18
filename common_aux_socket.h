//
// Created by andres on 8/10/20.
//

#include <stdlib.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include "common_aux_cipher.h"

#ifndef TP_1_CLIENT_CONNECTTOSOCKET_H
#define TP_1_CLIENT_CONNECTTOSOCKET_H

struct addrinfo {
   int              ai_flags;
   int              ai_family;
   int              ai_socktype;
   int              ai_protocol;
   socklen_t        ai_addrlen;
   struct sockaddr *ai_addr;
   char            *ai_canonname;
   struct addrinfo *ai_next;
};

int connectToSocket(char* host_name,char* port_name, int* socket_fd);
int sendMessage(int socket_fd, unsigned char* message, size_t len);
int shutdownAndClose(int socket_fd);
int bindToSocket(struct addrinfo* addrinfo, int* connct_sckt, int*
accpt_sckt, char* port_name);
size_t receiveMessage(int peer_socket, unsigned char*
buffer);
int closeSocket(int socket_fd);

#endif //TP_1_CLIENT_CONNECTTOSOCKET_H
