//
// Created by andres on 17/10/20.
//

#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include "client.h"

#define CHUNK_SIZE 64
#define CODE_OP 0
#define CLIENT_TYPE 0

int clientReadEncondeAndSend(client_t* self);

int clientInit(client_t* self) {
    memset(self, 0, sizeof(client_t));
    return 0;
}

int clientEstablishConnection(client_t* self, char* host, char* port) {
    socketInit(&self->socket, CLIENT_TYPE);
    return socketConnect(&self->socket, host, port);
}

size_t clientReadInput(client_t* self) {
    size_t counter = fread(self->buffer, 1, CHUNK_SIZE, stdin);
    return counter;
}

int clientSendMessage(client_t* self, char* host, char* port, char* method,
                      char* key) {
    int val_connect = clientEstablishConnection(self, host, port);
    if (val_connect != 0)
        return 1;
    int val_cipher_init = cipherInit(&self->cipher, method, key, CODE_OP);
    if (val_cipher_init != 0)
        return 1;
    while (!feof(stdin)) {
        int val_operation = clientReadEncondeAndSend(self);
        if (val_operation != 0)
            return 1;
    }
    return 0;
}

int clientEncodeChunk(client_t* self, size_t read_bytes) {
    if (! read_bytes)
        return 0;
    return cipherTranslate(&self->cipher, self->buffer, read_bytes);
}

int clientSendChunk(client_t* self, int read_bytes) {
    if (!read_bytes)
        return 0;
    return socketSendMessage(&self->socket, self->buffer, read_bytes);
}

int clientReadEncondeAndSend(client_t* self) {
    int read_bytes = clientReadInput(self);
    if (read_bytes < 0)
        return 1;
    int val_encode = clientEncodeChunk(self, read_bytes);
    if (val_encode != 0)
        return 1;
    int val_send = clientSendChunk(self, read_bytes);
    return val_send;
}

int clientClose(client_t* self, int ret_value) {
    if (&self->cipher) {
        if (cipherClose(&self->cipher) != 0)
            return 1;
    }
    if (&self->socket) {
        if (socketClose(&self->socket) != 0)
            return 1;
    }
    return ret_value;
}
