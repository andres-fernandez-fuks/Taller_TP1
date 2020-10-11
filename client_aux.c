//
// Created by andres on 10/10/20.
//

#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include "client_aux.h"

#define CHUNK_SIZE 64

size_t obtenerInputString(unsigned char* buffer) {
    size_t contador = 0;
    while (!feof(stdin)) {
        contador += fread(&buffer[contador],1,CHUNK_SIZE,stdin);
    }
    return contador;
}