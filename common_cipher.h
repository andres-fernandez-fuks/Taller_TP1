//
// Created by andres on 10/10/20.
//

#include "common_decoding.h"

#ifndef TP_1_COMMON_CIPHER_H
#define TP_1_COMMON_CIPHER_H


/*
 * Las 3 funciones de decodificacion reciben parametros parecidos, aunque no
 * exactamente los mismos. Para manejar la diferencia entre los parametros que
 * recibe cada funcion, uso el vector de punteros genericos "extra"/
 */

typedef int (*callback_t)(unsigned char* input, size_t len, unsigned char*
        buffer, void** extra);

typedef struct cipher{
    callback_t decoding_function;
    char* key_string;
    size_t type;
    size_t count;
    int op_type;
    unsigned char rc4_array[256];
    size_t rc4_pos2;
} cipher_t;

int cipherInit(cipher_t* self, char* method_name, char* key, int op_type);
int cipherEncoding(cipher_t* self,char* method_name);
int cipherDestroy(cipher_t* self);
int cipherTranslate(cipher_t* self, unsigned char* input, size_t len,
                    unsigned char* buffer);

#endif //TP_1_COMMON_CIPHER_H
