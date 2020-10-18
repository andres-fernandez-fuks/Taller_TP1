//
// Created by andres on 10/10/20.
//

#include "server_aux.h"
#include "common_aux.h"

#define DECODE_OP 1

int main(int argc, char** argv) {
    socket_t socket;
    initializeSocket(&socket);
    int val_bind = socketBind(&socket, argv[1]);
    if (val_bind != 0)
        return 1;
    bool shouldBreak = 0;
    cipher_t cipher;
    cipherCreate(&cipher, argv, DECODE_OP);
    while (!shouldBreak) {
        int val_rcv = receiveDecodeAndPrint(&cipher, &socket, argv,
                                            &shouldBreak);
        if (val_rcv != 0)
            return 1;
    }
    return finishProgram(&cipher, &socket);
}
