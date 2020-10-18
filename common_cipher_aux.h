//
// Created by andres on 10/10/20.
//

#ifndef TP_1_COMMON_CIPHER_AUX_H
#define TP_1_COMMON_CIPHER_AUX_H

#include <stdbool.h>
#include "common_cipher.h"

int stringEncode(cipher_t* cipher, unsigned char* input, unsigned char* output,
                 size_t len, char* key);
char* obtenerArgumento(char* argumento_original);
/*void multiFree(char* arg_1, char* arg_2);*/
int cipherCreate(cipher_t* cipher, char** argv, int op_type);

#endif //TP_1_COMMON_CIPHER_AUX_H
