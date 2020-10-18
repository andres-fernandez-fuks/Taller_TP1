//
// Created by andres on 17/10/20.
//

#include "server_aux.h"

int decode(cipher_t* cipher, unsigned char* coded_buffer, unsigned char*
decoded_buffer, size_t read_bytes, char** argv) {
    if (!read_bytes)
        return 0;
    char* key_string = obtenerArgumento(argv[3]);
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
    printOutput(decoded_buffer, read_bytes);
    if (read_bytes <64) {
        *shouldBreak = 1;
    }
    return 0;
}

int finishServerProgram(cipher_t* cipher, rSocket_t* socket) {
    if (cipherDestroy(cipher) != 0)
        return 1;
    return receptorSocketClose(socket);
}

void printOutput(unsigned char* cadena_encriptada, size_t largo_cadena) {
    for (size_t i = 0; i < largo_cadena; ++i)
        printf("%c",cadena_encriptada[i]);
}
