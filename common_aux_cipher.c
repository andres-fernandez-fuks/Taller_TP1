#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>
#include <stdbool.h>
#include "common_cipher.h"

#define CODE_OP 0
#define DECODE_OP 1

#include "common_aux_cipher.h"

int stringEncode(cipher_t* cipher, unsigned char* input, unsigned char* output,
                 size_t len, char* key) {
    if (!key)
        return 1;
    return cipherTranslate(cipher, input, len, output);
}

void multiFree(char* arg_1, char* arg_2) {
    if (arg_1)
        free(arg_1);
    if (arg_2)
        free(arg_2);
}

int cipherCreate(cipher_t* cipher, char** argv, int op_type) {
    char* method_name = NULL;
    char* key_string = NULL;
    if (op_type == CODE_OP) {
        method_name = obtenerArgumento(argv[3]);
        key_string = obtenerArgumento(argv[4]);
    } else {
        method_name = obtenerArgumento(argv[2]);
        key_string = obtenerArgumento(argv[3]);
    }
    memset(cipher, 0, sizeof(cipher_t));
    int init_ok = cipherInit(cipher, method_name, key_string, op_type);
    multiFree(method_name, key_string);
    return init_ok;
}

char* obtenerArgumento(char* argumento_original) {
    char* pos_nombre_arg = strrchr(argumento_original,'=');
    if (!pos_nombre_arg) return NULL;
    pos_nombre_arg += 1; // la posicion real es la proxima al "="
    int largo_nombre_arg = strlen(argumento_original)-(pos_nombre_arg-
                                                       argumento_original);
    char* argumento = malloc(largo_nombre_arg+1);
    strncpy(argumento,pos_nombre_arg,largo_nombre_arg);
    argumento[largo_nombre_arg] = '\0';
    return argumento;
}




