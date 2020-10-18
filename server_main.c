//
// Created by andres on 10/10/20.
//


#include <stdio.h>
#include "common_aux_cipher.h"
#include "server_receptorSocket.h"

#define DECODE_OP 1

int decode(cipher_t* cipher, unsigned char* coded_buffer, unsigned char*
        decoded_buffer, size_t read_bytes, char** argv);
        int initializeReceptorSocket(rSocket_t* socket);
int receiveDecodeAndPrint(cipher_t* cipher, rSocket_t* socket, char** argv,
                          bool* shouldBreak);


int main(int argc, char** argv) {
    rSocket_t r_socket;
    initializeReceptorSocket(&r_socket);
    int val_bind = socketBind(&r_socket, argv[1]);
    if (val_bind != 0)
        return 1;
    bool shouldBreak = 0;
    cipher_t cipher;
    cipher_create(&cipher, argv, DECODE_OP);
    while (1) {
        int val_rcv = receiveDecodeAndPrint(&cipher, &r_socket, argv,
                                            &shouldBreak);
        if (val_rcv != 0)
            return 1;
        if (shouldBreak)
            break;
    }
    receptorSocketClose(&r_socket);
    cipherDestroy(&cipher);
    return 0;
}

int decode(cipher_t* cipher, unsigned char* coded_buffer, unsigned char*
        decoded_buffer, size_t read_bytes, char** argv) {
    if (!read_bytes)
        return 0;
    char* key_string = obtener_argumento(argv[3]);
    int val_encode = stringEncode(cipher, coded_buffer, decoded_buffer,
                                  read_bytes, key_string);
    free(key_string);
    return val_encode;
}

int initializeReceptorSocket(rSocket_t* socket) {
    memset(socket,0,sizeof(rSocket_t));
    return receptorSocketInit(socket);
}

int receiveDecodeAndPrint(cipher_t* cipher, rSocket_t* socket, char** argv,
                          bool* shouldBreak) {
    unsigned char coded_buffer[64] = {0};
    size_t read_bytes = socketReceiveMessage(socket, coded_buffer);
    unsigned char decoded_buffer[64] = {0};
    int val_decoding = decode(cipher, coded_buffer, decoded_buffer, read_bytes,
                              argv);
    if (val_decoding != 0)
        return 1;
    printString(decoded_buffer, read_bytes, "%c");
    if (read_bytes <64) {
        *shouldBreak = 1;
    }
    return 0;
}
