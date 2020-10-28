//
// Created by andres on 10/10/20.
//

#include "server.h"
#include "common_parsing.h"

#define DECODE_OP 1

int main(int argc, char** argv) {
    server_t server;
    int val_init = serverInit(&server);
    if (val_init != 0)
        return 1;

    char* port = argv[1];
    char* method = obtenerArgumento(argv[2]);
    char* key = obtenerArgumento(argv[3]);
    int val_receive = serverReceiveMessage(&server, port, method, key);
    return serverClose(&server, val_receive);
}
