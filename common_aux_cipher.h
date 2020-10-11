//
// Created by andres on 10/10/20.
//

#ifndef TP_1_COMMON_AUX_CIPHER_H
#define TP_1_COMMON_AUX_CIPHER_H

#include <stdbool.h>

int stringEncode(unsigned char* input, unsigned char* output, size_t len,
                 char* method, char* key, bool op_type);
char* obtener_argumento(char* argumento_original);
void imprimir_cadena(unsigned char* cadena_encriptada,size_t largo_cadena, char* format);
char* definirEncriptacionDeCadena(char* input_string,char* nombre_metodo,char* clave);

#endif //TP_1_COMMON_AUX_CIPHER_H
