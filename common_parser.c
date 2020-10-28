//
// Created by andres on 18/10/20.
//

#include <string.h>
#include "common_parser.h"

#define CODE_OP 0
#define DECODE_OP 1

char* parserObtenerArgumento(char* argumento_original) {
    char* pos_nombre_arg = strrchr(argumento_original,'=');
    if (!pos_nombre_arg) return NULL;
    pos_nombre_arg += 1; // la posicion real es la proxima al "="
    return pos_nombre_arg;
}
