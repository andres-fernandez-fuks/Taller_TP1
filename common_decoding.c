///
// Created by andres on 7/10/20.

#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include "common_decoding.h"

#define TOTAL_CARACTERES 256
#define CODE_OP 0
#define DECODE_OP 1

void swap(unsigned char* arreglo, unsigned int pos_1, unsigned int pos_2) {
    unsigned char temp = arreglo[pos_1];
    arreglo[pos_1] = arreglo[pos_2];
    arreglo[pos_2] = temp;
}

void rc4_init(unsigned char* arreglo_random, unsigned char* key, unsigned int
    key_length) {
    unsigned int i,j;
    for (i = 0; i < 256; ++i)
        arreglo_random[i] = i;

    for (i = j = 0; i < 256; ++i) {
        j = (j + key[i % key_length] + arreglo_random[i]) & 255;
        swap(arreglo_random, i, j);
    }
}

unsigned char rc4_output(unsigned char* arreglo_random,size_t* pos_1, size_t*
            pos_2) {
    *pos_1 = (*pos_1+1) & 255;
    *pos_2 = (*pos_2+ arreglo_random[*pos_1]) & 255;
    swap(arreglo_random,*pos_1,*pos_2);
    return arreglo_random[(arreglo_random[*pos_1]+arreglo_random[*pos_2])&255];
}

int vigenere_encoding(unsigned char* input, size_t len, char* key_string,
                      unsigned char* buffer, void** extra) {
    size_t key_length = strlen(key_string);
    int op_type = *(int*) extra[0];
    size_t* pos_actual = (size_t*) extra[1];
    unsigned char* key = (unsigned char*) key_string;

    for (size_t i = 0; i < len; i++) {
        int pos_clave = (i+*pos_actual)%key_length;
        if (op_type == CODE_OP)
            buffer[i] = (input[i] + key[pos_clave])%256;
        else
            buffer[i] = (input[i] - key[pos_clave])%256;
    }
    *pos_actual += len;
    return 0;
}

int rc4_encoding(unsigned char* input, size_t len, char* key_string, unsigned
        char* buffer, void** extra) {
    unsigned char* arreglo_random = (unsigned char*) extra[0];
    size_t* pos_1 = (size_t*) extra[1];
    size_t* pos_2 = (size_t*) extra[2];
    size_t key_length = strlen(key_string);
    char* copia_clave = malloc(key_length);
    strncpy(copia_clave,key_string,key_length);

    for (size_t i = 0; i < len; ++i) {
        buffer[i] = (unsigned char) input[i] ^ rc4_output(arreglo_random,
                                                          pos_1, pos_2);
    }
    free(copia_clave);
    return 0;
}

int cesar_encoding(unsigned char* input, size_t len, char* offset_string,
                   unsigned char* buffer, void** extra) {
    int offset = atoi(offset_string);
    int op_type = * (int*) extra[0];
    for (size_t i = 0; i < len; ++i) {
        if (op_type == CODE_OP)
            buffer[i] = (input[i] + offset)%TOTAL_CARACTERES;
        else
            buffer[i] = (input[i] - offset)%TOTAL_CARACTERES;
    }
    return 0;
}
