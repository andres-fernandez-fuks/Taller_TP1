//
// Created by andres on 10/10/20.
//

#include "server.h"
#include "common_parsing.h"

#define DECODE_OP 1

int main(int argc, char** argv) {
    server_t server;
    initializeServer(&server);
    int val_bind = serverEstablishConnection(&server, argv[1]);
    if (val_bind != 0)
        return finishServerProgram(&server, 1);
    char* method = obtenerArgumento(argv[2]);
    char* key = obtenerArgumento(argv[3]);
    int val_receive = serverReceiveMessage(&server, method, key);
    return finishServerProgram(&server, val_receive);
}
