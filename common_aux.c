//
// Created by andres on 18/10/20.
//

#include <string.h>
#include "common_aux.h"

#define CODE_OP 0
#define DECODE_OP 1

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
    return init_ok;
}

int initializeSocket(socket_t* socket) {
    memset(socket,0,sizeof(socket_t));
    return socketInit(socket);
}

int finishProgram(cipher_t* cipher, socket_t* socket, int ret_value) {
    if (cipher) {
        if (cipherDestroy(cipher) != 0)
            return 1;
    }
    if (socket) {
        if (socketClose(socket) != 0)
            return 1;
    }
    return ret_value;
}
