//
// Created by andres on 17/10/20.
//

#include "common_cipher.h"
#include "common_socket.h"

#ifndef TP_1_CLIENT_AUX_H
#define TP_1_CLIENT_AUX_H
#define CHUNK_SIZE 64

typedef struct client{
    cipher_t cipher;
    socket_t socket;
    unsigned char buffer[CHUNK_SIZE];
} client_t;


int clientInit(client_t* self);
int clientSendMessage(client_t* self, char* host, char* port, char* method,
                      char* key);
int clientClose(client_t* self, int ret_value);

#endif //TP_1_CLIENT_AUX_H
