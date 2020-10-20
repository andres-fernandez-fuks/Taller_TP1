#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>
#include <stdbool.h>
#include "common_cipher.h"

#define CODE_OP 0
#define DECODE_OP 1

#include "common_cipher_aux.h"

int stringEncode(cipher_t* cipher, unsigned char* input, unsigned char* output,
                 size_t len, char* key) {
    if (!key)
        return 1;
    return cipherTranslate(cipher, input, len, output);
}

char* obtenerArgumento(char* argumento_original) {
    char* pos_nombre_arg = strrchr(argumento_original,'=');
    if (!pos_nombre_arg) return NULL;
    pos_nombre_arg += 1; // la posicion real es la proxima al "="
    return pos_nombre_arg;
}




