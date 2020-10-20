///
// Created by andres on 7/10/20.

#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include "common_decoding.h"

#define TOTAL_CARACTERES 256
#define CODE_OP 0
#define DECODE_OP 1

int cesarEncoding(unsigned char* input, size_t len, unsigned char* buffer,
                  void** extra) {
    int op_type = * (int*) extra[0];
    int offset = atoi((char*) extra[1]);
    for (size_t i = 0; i < len; ++i) {
        if (op_type == CODE_OP)
            buffer[i] = (input[i] + offset)%TOTAL_CARACTERES;
        else
            buffer[i] = (input[i] - offset)%TOTAL_CARACTERES;
    }
    return 0;
}

int vigenereEncoding(unsigned char* input, size_t len, unsigned char* buffer,
                     void** extra) {
    int op_type = *(int*) extra[0];
    size_t* current_pos = (size_t*) extra[1];
    size_t key_length = strlen((char*) extra[2]);
    unsigned char* key = (unsigned char*) extra[2];

    for (size_t i = 0; i < len; i++) {
        int pos_clave = (i+*current_pos) % key_length;
        if (op_type == CODE_OP)
            buffer[i] = (input[i] + key[pos_clave])%256;
        else
            buffer[i] = (input[i] - key[pos_clave])%256;
    }
    *current_pos += len;
    return 0;
}

void rc4Swap(unsigned char* array, unsigned int pos_1, unsigned int pos_2) {
    unsigned char temp = array[pos_1];
    array[pos_1] = array[pos_2];
    array[pos_2] = temp;
}

void rc4InitiateVector(unsigned char* random_array, unsigned char* key,
                       unsigned int key_length) {
    unsigned int i,j;
    for (i = 0; i < 256; ++i)
        random_array[i] = i;

    for (i = j = 0; i < 256; ++i) {
        j = (j + key[i % key_length] + random_array[i]) & 255;
        rc4Swap(random_array, i, j);
    }
}

unsigned char rc4Output(unsigned char* random_array, size_t* pos_1, size_t*
pos_2) {
    *pos_1 = (*pos_1+1) & 255;
    *pos_2 = (*pos_2 + random_array[*pos_1]) & 255;
    rc4Swap(random_array, *pos_1, *pos_2);
    return random_array[(random_array[*pos_1] + random_array[*pos_2]) & 255];
}

int rc4Encoding(unsigned char* input, size_t len, unsigned char* buffer,
                void** extra) {
    unsigned char* arreglo_random = (unsigned char*) extra[0];
    size_t* pos_1 = (size_t*) extra[1];
    size_t* pos_2 = (size_t*) extra[2];

    for (size_t i = 0; i < len; ++i) {
        buffer[i] = (unsigned char) input[i] ^ rc4Output(arreglo_random,
                                                         pos_1, pos_2);
    }

    return 0;
}


