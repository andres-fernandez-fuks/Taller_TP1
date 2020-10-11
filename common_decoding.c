//
// Created by andres on 7/10/20.

#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "common_decoding.h"

#define TOTAL_CARACTERES 256
#define CODE_OP 0
#define DECODE_OP 1

int cesar_encoding(unsigned char* input, size_t len, char* key_string,
                                 unsigned char* buffer, size_t op_type) {
    int offset = atoi(key_string);
    for (size_t i = 0; i < len; ++i) {
        if (op_type == CODE_OP)
            buffer[i] = (input[i] + offset)%TOTAL_CARACTERES;
        else
            buffer[i] = (input[i] - offset)%TOTAL_CARACTERES;
    }
    return 0;
}

int vigenere_encoding(unsigned char* input, size_t len, char* key_string,
                                 unsigned char* buffer, size_t op_type) {
    size_t key_length = strlen(key_string);
    unsigned char* key = key_string;
    for (size_t i = 0; i < len; ++i) {
        int pos_clave = i%key_length;
        if (op_type == CODE_OP)
            buffer[i] = (input[i] + key[pos_clave])%256;
        else
            buffer[i] = (input[i] - key[pos_clave])%256;
    }
    return 0;
}

void swap(unsigned char* arreglo, unsigned int pos_1, unsigned int pos_2) {
    unsigned char temp = arreglo[pos_1];
    arreglo[pos_1] = arreglo[pos_2];
    arreglo[pos_2] = temp;
}

void rc4_init(unsigned char* arreglo_random, unsigned char* key, unsigned int key_length) {
    unsigned int i,j;
    for (i = 0; i < 256; ++i)
        arreglo_random[i] = i;

    for (i = j = 0; i < 256; ++i) {
        j = (j + key[i % key_length] + arreglo_random[i]) & 255;
        swap(arreglo_random, i, j);
    }
}

unsigned char rc4_output(unsigned char* arreglo_random,size_t pos_actual) {
    static unsigned int pos_1,pos_2 = 0;
    if (pos_actual == 0) { // esto es medio feo, pero si codifico y decodifico
        pos_1 = 0;         // el mismo proceso, necesito reiniciar ambos al
        pos_2 = 0;         // inicio de la codificacion
    }
    pos_1 = (pos_1+1) & 255;
    pos_2 = (pos_2+ arreglo_random[pos_1]) & 255;
    swap(arreglo_random,pos_1,pos_2);
    return arreglo_random[(arreglo_random[pos_1]+arreglo_random[pos_2]) & 255];
}

int rc4_encoding(unsigned char* input, size_t len, char* key_string,
                               unsigned char* buffer, size_t op_type) {

    size_t key_length = strlen(key_string);
    char* copia_clave = malloc(key_length);
    strncpy(copia_clave,key_string,key_length);
    char* arreglo_random = malloc(256);
    rc4_init(arreglo_random,copia_clave,key_length);

    for (size_t i = 0; i < len; ++i) {
        buffer[i] = (unsigned char) input[i] ^ rc4_output(arreglo_random,i);
    }
    free(arreglo_random);
    free(copia_clave);
    return 0;
}

