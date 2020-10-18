//
// Created by andres on 18/10/20.
//

#include <string.h>
#include "common_aux.h"


int initializeSocket(socket_t* socket) {
    memset(socket,0,sizeof(socket_t));
    return socketInit(socket);
}

int finishProgram(cipher_t* cipher, socket_t* socket) {
    if (cipherDestroy(cipher) != 0)
        return 1;
    return socketClose(socket);
}
