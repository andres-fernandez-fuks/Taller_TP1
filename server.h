//
// Created by andres on 17/10/20.
//

#ifndef TP_1_SERVER_H
#define TP_1_SERVER_H

#include <stdbool.h>
#include "common_cipher.h"
#include "common_socket.h"

#define CHUNK_SIZE 64

typedef struct server{
    cipher_t cipher;
    socket_t connection_socket;
    socket_t acceptance_socket;
    unsigned char buffer[CHUNK_SIZE];
} server_t;

int serverInit(server_t* self);
int serverReceiveMessage(server_t* server,char* port, char* method_name,
                         char* key);
int serverClose(server_t* server, int ret_value);


#endif //TP_1_SERVER_H
