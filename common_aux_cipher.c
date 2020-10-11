#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>
#include <stdbool.h>
#include "common_cipher.h"

#define CODE_OP 0
#define DECODE_OP 1
#define ERROR_ARGS 1
#define ERROR_STDIN 2
#define ERROR_CIPHER 3

#include "common_aux_cipher.h"

int stringEncode(unsigned char* input, unsigned char* output, size_t len,
                 char* method, char* key, bool op_type) {
    if (!method || !key)
        return 1;
    cipher_t cipher;
    memset(&cipher,0,sizeof(cipher_t));
    cipherInit(&cipher,method);

    switch (op_type) {
        case 0:
            return cipherCode(&cipher, input, len, key, output);
        case 1:
            return cipherDecode(&cipher, input, len, key, output);
    }
}

char* obtener_argumento(char* argumento_original) {
    char* pos_nombre_arg = strrchr(argumento_original,'=');
    if (!pos_nombre_arg) return NULL;
    pos_nombre_arg += 1; // la posicion real es la proxima al "="
    size_t largo_nombre_arg = strlen(argumento_original)-((int)pos_nombre_arg-(int)argumento_original);
    char* argumento = malloc(largo_nombre_arg+1);
    strncpy(argumento,pos_nombre_arg,largo_nombre_arg);
    argumento[largo_nombre_arg] = '\0';
    return argumento;
}

void imprimir_cadena(unsigned char* cadena_encriptada,size_t largo_cadena, char* format) {
    for (size_t i = 0; i < largo_cadena; ++i)
        printf(format,cadena_encriptada[i]);
    puts("");
}

