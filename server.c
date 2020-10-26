//
// Created by andres on 17/10/20.
//

#include <string.h>
#include <stdio.h>
#include "server.h"

#define CHUNK_SIZE 64
#define DECODE_OP 1

size_t receiveChunk(server_t* self);
int decodeAndPrintChunk(server_t* self, size_t read_bytes);

void printOutput(unsigned char* cadena_encriptada, size_t largo_cadena) {
    fwrite(cadena_encriptada, 1, largo_cadena, stdout);
}

int initializeServer(server_t* self) {
    memset(self, 0, sizeof(server_t));
}

int finishServerProgram(server_t* server, int ret_value) {
    if (&server->cipher) {
        if (cipherDestroy(&server->cipher) != 0)
            return 1;
    }
    if (&server->connection_socket) {
        if (socketClose(&server->connection_socket) != 0)
            return 1;
    }
    if (&server->acceptance_socket) {
        if (socketClose(&server->acceptance_socket) != 0)
            return 1;
    }
    return ret_value;
}

int serverReceiveMessage(server_t* self, char* method, char* key) {
    int val_cipher_init = cipherInit(&self->cipher, method, key, DECODE_OP);
    if (val_cipher_init != 0)
        return 1;
    bool should_break = 0;
    while (true) {
        size_t read_bytes = receiveChunk(self);
        if (!read_bytes)
            return 1;
        int val_decode = decodeAndPrintChunk(self, read_bytes);
        if (val_decode != 0)
            return 1;
        if (read_bytes < CHUNK_SIZE)
            break;
    }
}

int serverEstablishConnection(server_t* self, char* port) {
    socketInit(&self->connection_socket);
    socketInit(&self->acceptance_socket);
    int val_bind = socketBind(&self->connection_socket, port);
    if (val_bind != 0)
        return 1;

    int val_accept = socketAcceptConnection(&self->connection_socket,
                                            &self->acceptance_socket);
    return val_accept;
}

size_t receiveChunk(server_t* self) {
    socketReceiveMessage(&self->acceptance_socket, self->read_buffer);
}

int decodeAndPrintChunk(server_t* self, size_t read_bytes) {
    int val_translate = cipherTranslate(&self->cipher, self->read_buffer,
                                        read_bytes, self->decoded_buffer);
    if (val_translate != 0)
        return 1;
    printOutput(self->decoded_buffer, read_bytes);
    return 0;
}

