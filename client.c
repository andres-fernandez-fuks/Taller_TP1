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

int encodeAndSendChunk(client_t* self, size_t read_bytes);

int encodeMessage(client_t* self, size_t read_bytes) {
    if (! read_bytes)
        return 0;
    return cipherTranslate(&self->cipher, self->buffer, read_bytes);
}

int initializeClient(client_t* self) {
    memset(self, 0, sizeof(client_t));
    return 0;
}

int clientEstablishConnection(client_t* self, char* host, char* port) {
    socketInit(&self->socket, CLIENT_TYPE);
    return socketConnect(&self->socket, host, port);
}

size_t readInput(client_t* self) {
    size_t contador = fread(self->buffer, 1, CHUNK_SIZE, stdin);
    return contador;
}

int clientSendMessage(client_t* self, char* method, char* key) {
    int val_cipher_init = cipherInit(&self->cipher, method, key, CODE_OP);
    if (val_cipher_init != 0)
        return 1;
    while (!feof(stdin)) {
        size_t read_bytes = readInput(self);
        if (!read_bytes)
            return 1;
        int val_send = encodeAndSendChunk(self, read_bytes);
        if (val_send != 0)
            return 1;
    }
    return 0;
}

int encodeAndSendChunk(client_t* self, size_t read_bytes) {
    int val_encoding = encodeMessage(self, read_bytes);
    if (val_encoding != 0)
        return 1;
    return socketSendMessage(&self->socket, self->buffer, read_bytes);
}

int finishClientProgram(client_t* client, int ret_value) {
    if (&client->cipher) {
        if (cipherDestroy(&client->cipher) != 0)
            return 1;
    }
    if (&client->socket) {
        if (socketClose(&client->socket) != 0)
            return 1;
    }
    return ret_value;
}
