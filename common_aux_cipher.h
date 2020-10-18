//
// Created by andres on 10/10/20.
//

#ifndef TP_1_COMMON_AUX_CIPHER_H
#define TP_1_COMMON_AUX_CIPHER_H

#include <stdbool.h>
#include "common_cipher.h"

int stringEncode(cipher_t* cipher, unsigned char* input, unsigned char* output,
                 size_t len, char* key);
char* obtener_argumento(char* argumento_original);
void printString(unsigned char* cadena_encriptada, size_t largo_cadena,
	char* format);
char* definirEncriptacionDeCadena(char* input_string,char* nombre_metodo,
	char* clave);
void multiFree(char* arg_1, char* arg_2);
int cipher_create(cipher_t* cipher, char** argv, int op_type);

#endif //TP_1_COMMON_AUX_CIPHER_H
