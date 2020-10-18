//
// Created by andres on 10/10/20.
//

#include "server_aux.h"

#define DECODE_OP 1

int main(int argc, char** argv) {
    rSocket_t r_socket;
    initializeReceptorSocket(&r_socket);
    int val_bind = socketBind(&r_socket, argv[1]);
    if (val_bind != 0)
        return 1;
    bool shouldBreak = 0;
    cipher_t cipher;
    cipherCreate(&cipher, argv, DECODE_OP);
    while (!shouldBreak) {
        int val_rcv = receiveDecodeAndPrint(&cipher, &r_socket, argv,
                                            &shouldBreak);
        if (val_rcv != 0)
            return 1;
    }
    return finishServerProgram(&cipher, &r_socket);
}
