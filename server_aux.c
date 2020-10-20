//
// Created by andres on 17/10/20.
//

#include <string.h>
#include <stdio.h>
#include "server_aux.h"

#define CHUNK_SIZE 64

int decode(cipher_t* cipher, unsigned char* coded_buffer, unsigned char*
decoded_buffer, size_t read_bytes, char** argv) {
    if (!read_bytes)
        return 0;
    char* key_string = obtenerArgumento(argv[3]);
    int val_encode = stringEncode(cipher, coded_buffer, decoded_buffer,
                                  read_bytes, key_string);
    return val_encode;
}

int receiveDecodeAndPrint(cipher_t* cipher, socket_t* socket, char** argv,
                          bool* shouldBreak) {
    unsigned char coded_buffer[CHUNK_SIZE] = {0};
    size_t read_bytes = socketReceiveMessage(socket, coded_buffer);
    unsigned char decoded_buffer[CHUNK_SIZE] = {0};
    int val_decoding = decode(cipher, coded_buffer, decoded_buffer, read_bytes,
                              argv);
    if (val_decoding != 0)
        return 1;
    printOutput(decoded_buffer, read_bytes);
    if (read_bytes < CHUNK_SIZE) {
        *shouldBreak = 1;
    }
    return 0;
}

void printOutput(unsigned char* cadena_encriptada, size_t largo_cadena) {
    for (size_t i = 0; i < largo_cadena; ++i)
        printf("%c",cadena_encriptada[i]);
}
