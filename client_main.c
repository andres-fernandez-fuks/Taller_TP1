//
// Created by andres on 10/10/20.
//


#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "common_aux_socket.h"
#include "common_aux_cipher.h"
#include "client_transmitterSocket.h"
#include "common_cipher.h"

#define CODE_OP 0
#define READ_SIZE 64

int encodeMessage(cipher_t* cipher, unsigned char* input_buf, unsigned char*
encoded_buf, size_t read_bytes, char** argv);
void multiFree(char* arg_1, char* arg_2);
int initializeTransmisionSocket(tSocket_t* socket);
int readEncodeAndSend(cipher_t* cipher, tSocket_t* socket, char** argv);
size_t obtenerInputString(unsigned char* buffer);

int main(int argc, char** argv) {
    tSocket_t t_socket;
    initializeTransmisionSocket(&t_socket);
    int val_connect = socketConnect(&t_socket, argv[1], argv[2]);
	if (val_connect != 0)
		return 1;
	cipher_t cipher;
	cipher_create(&cipher, argv, CODE_OP);
	while (!feof(stdin)) {
        if (readEncodeAndSend(&cipher, &t_socket, argv) != 0)
            return 1;
    }
    transmissionSocketClose(&t_socket);
    cipherDestroy(&cipher);
    return 0;
}

int initializeTransmisionSocket(tSocket_t* socket) {
    memset(socket, 0, sizeof(tSocket_t));
    return transmissionSocketInit(socket);
}

int encodeMessage(cipher_t* cipher, unsigned char* input_buf, unsigned char*
        encoded_buf, size_t read_bytes, char** argv) {
    char* key_string = obtener_argumento(argv[4]);
    int encoding = 1;
    if (key_string) {
        encoding = stringEncode(cipher, input_buf, encoded_buf, read_bytes,
                                key_string);
    }
    free(key_string);
    return encoding;
}

int readEncodeAndSend(cipher_t* cipher, tSocket_t* socket, char** argv) {
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


