//
// Created by andres on 10/10/20.
//

#include <stdio.h>
#include "client_aux.h"

#define CODE_OP 0
#define READ_SIZE 64

int main(int argc, char** argv) {
    tSocket_t t_socket;
    initializeTransmisionSocket(&t_socket);
    int val_connect = socketConnect(&t_socket, argv[1], argv[2]);
	if (val_connect != 0)
		return 1;
	cipher_t cipher;
    cipherCreate(&cipher, argv, CODE_OP);
	while (!feof(stdin)) {
        if (readEncodeAndSend(&cipher, &t_socket, argv) != 0)
            return 1;
    }
    return finishClientProgram(&cipher, &t_socket);
}



