//
// Created by andres on 10/10/20.
//

#include <stdio.h>
#include "client.h"
#include "common_parsing.h"

#define CODE_OP 0

int main(int argc, char** argv) {
    client_t client;
    initializeClient(&client);
    int val_connect = clientEstablishConnection(&client, argv[1], argv[2]);
    if (val_connect != 0)
        return finishClientProgram(&client, 1);
    char* method = obtenerArgumento(argv[3]);
    char* key = obtenerArgumento(argv[4]);
    int val_send = clientSendMessage(&client, method, key);
    return finishClientProgram(&client, val_send);
}
