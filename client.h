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
    unsigned char read_buffer[CHUNK_SIZE];
    unsigned char encoded_buffer[CHUNK_SIZE];
} client_t;

int encodeMessage(client_t* self, size_t read_bytes);
int initializeClient(client_t* self);
int clientEstablishConnection(client_t* self, char* host, char* port);
int clientSendMessage(client_t* self, char* method, char* name);
int finishClientProgram(client_t* self, int ret_value);

#endif //TP_1_CLIENT_AUX_H
