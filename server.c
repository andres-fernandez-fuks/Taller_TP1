//
// Created by andres on 17/10/20.
//

#include <string.h>
#include <stdio.h>
#include "server.h"

#define CHUNK_SIZE 64
#define DECODE_OP 1
#define SERVER_TYPE 1

int serverReceiveDecodeAndPrint(server_t* self, bool* keep_receiving);

size_t serverPrintOutput(unsigned char* cadena_encriptada, size_t largo_cadena){
    return fwrite(cadena_encriptada, 1, largo_cadena, stdout);
}

int serverInit(server_t* self) {
    memset(self, 0, sizeof(server_t));
    return 0;
}

int serverClose(server_t* server, int ret_value) {
    if (cipherClose(&server->cipher) != 0)
        return 1;

    if (socketClose(&server->connection_socket) != 0)
        return 1;

    if (socketClose(&server->acceptance_socket) != 0)
        return 1;

    return ret_value;
}

int serverEstablishConnection(server_t* self, char* port) {
    socketInit(&self->connection_socket, SERVER_TYPE);
    socketInit(&self->acceptance_socket, SERVER_TYPE);
    int val_bind = socketConnect(&self->connection_socket, NULL, port);
    if (val_bind != 0)
        return 1;

    int val_accept = socketAcceptConnection(&self->connection_socket,
                                            &self->acceptance_socket);
    return val_accept;
}

int serverReceiveMessage(server_t* self, char* port, char* method, char* key) {
    int val_connect = serverEstablishConnection(self, port);
    if (val_connect != 0)
        return 1;
    int val_cipher_init = cipherInit(&self->cipher, method, key, DECODE_OP);
    if (val_cipher_init != 0)
        return 1;
    bool keep_receiving = true;
    while (keep_receiving) {
        int val_operation = serverReceiveDecodeAndPrint(self, &keep_receiving);
        if (val_operation != 0)
            return 1;
    }
    return 0;
}

int serverReceiveChunk(server_t* self) {
    return socketReceiveMessage(&self->acceptance_socket, self->buffer);
}


int serverDecodeChunk(server_t* self, int read_bytes) {
    if (!read_bytes)
        return 0;
    int val_trnslate = cipherTranslate(&self->cipher, self->buffer, read_bytes);
    if (val_trnslate != 0)
        return 1;
    return 0;
}

int serverPrintChunk(server_t* self, int read_bytes) {
    if (!read_bytes)
        return 0;
    size_t written_bytes = serverPrintOutput(self->buffer, read_bytes);
    if ((int) written_bytes == read_bytes)
        return 0;
    return 1;
}

int serverReceiveDecodeAndPrint(server_t* self, bool* keep_receiving) {
    int read_bytes = serverReceiveChunk(self);
    if (read_bytes < 1)
        return 1;
    int val_decode = serverDecodeChunk(self, read_bytes);
    if (val_decode != 0)
        return 1;
    int val_print = serverPrintChunk(self, read_bytes);
    if (val_print != 0)
        return 1;
    if (read_bytes < CHUNK_SIZE)
        *keep_receiving = false;
    return 0;
}







