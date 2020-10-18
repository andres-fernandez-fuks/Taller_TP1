//
// Created by andres on 17/10/20.
//

#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include "client_aux.h"

#define READ_SIZE 64

int encodeMessage(cipher_t* cipher, unsigned char* input_buf, unsigned char*
encoded_buf, size_t read_bytes, char** argv) {
    char* key_string = obtenerArgumento(argv[4]);
    int encoding = 1;
    if (key_string) {
        encoding = stringEncode(cipher, input_buf, encoded_buf, read_bytes,
                                key_string);
    }
    //free(key_string);
    return encoding;
}

int readEncodeAndSend(cipher_t* cipher, socket_t* socket, char** argv) {
    unsigned char input_buffer[READ_SIZE] = {0};
    size_t read_bytes = obtenerInputString(input_buffer);
    if (!read_bytes)
        return 1;
    unsigned char encoded_buffer[read_bytes];
    int val_encoding = encodeMessage(cipher, input_buffer,encoded_buffer,
                                     read_bytes, argv);
    if (val_encoding != 0)
        return 1;
    return socketSendMessage(socket, encoded_buffer, read_bytes);
}

size_t obtenerInputString(unsigned char* buffer) {
    size_t contador = fread(buffer,1,READ_SIZE,stdin);
    return contador;
}
