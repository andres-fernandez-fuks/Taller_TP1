//
// Created by andres on 10/10/20.
//

#include <stdio.h>
#include "client_aux.h"
#include "common_aux.h"

#define CODE_OP 0
#define READ_SIZE 64

int main(int argc, char** argv) {
    socket_t socket;
    initializeSocket(&socket);
    int val_connect = socketConnect(&socket, argv[1], argv[2]);
	if (val_connect != 0)
		return finishProgram(NULL, &socket, 1);
	cipher_t cipher;
    cipherCreate(&cipher, argv, CODE_OP);
	while (!feof(stdin)) {
        if (readEncodeAndSend(&cipher, &socket, argv) != 0)
            return finishProgram(&cipher, &socket, 1);
    }
    return finishProgram(&cipher, &socket, 0);
}



