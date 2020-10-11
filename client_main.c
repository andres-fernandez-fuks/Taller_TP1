//
// Created by andres on 10/10/20.
//

#include <limits.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "client_conectarAlSocket.h"
#include "client_aux.h"
#include "common_aux_cipher.h"
#include "client_main.h"

#define CODE_OP 0

void send_message(unsigned char* buffer, size_t bytes_leidos, char* host, char* port);
void inputReadOk(char* input_buffer, size_t len);
int encodeMessage(char* input_buf, char* encoded_buf, size_t read_bytes, char** argv);
void multiFree(char* arg_1, char* arg_2);

int client_main(int argc, char** argv) {
    unsigned char input_buffer[PATH_MAX];
    size_t read_bytes = obtenerInputString(input_buffer);
    if (!read_bytes)
        return 1;
    inputReadOk(input_buffer, read_bytes);
    unsigned char encoded_buffer[read_bytes];
    int val_encoding = encodeMessage(input_buffer,encoded_buffer,read_bytes,argv);
    if (!val_encoding == 0)
        return 1;
    puts("Mensaje decodificado correctamente");
    send_message(encoded_buffer, read_bytes,argv[2],argv[3]);
    return 0;
}

void send_message(unsigned char* buffer, size_t len, char* host, char* port) {
    puts("Enviando mensaje...");
    connectToSocket(buffer, len, host, port);
}

void inputReadOk(char* input_buffer, size_t len) {
    printf("Mensaje leído correctamente: ");
    imprimir_cadena(input_buffer,len,"%c");
}

int encodeMessage(char* input_buf, char* encoded_buf, size_t read_bytes, char** argv) {
    char* method_name = obtener_argumento(argv[4]);
    char* key_string = obtener_argumento(argv[5]);
    puts("Codificando mensaje...");
    int encoding = 1;
    if (key_string && method_name) {
        encoding = stringEncode(input_buf, encoded_buf, read_bytes,
                                method_name, key_string, CODE_OP);
    }
    multiFree(method_name,key_string);
    return encoding;
}

void multiFree(char* arg_1, char* arg_2) {
    if (arg_1)
        free(arg_1);
    if (arg_2)
        free(arg_2);
}
