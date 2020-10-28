//
// Created by andres on 10/10/20.
//

#include "client.h"
#include "common_parsing.h"

#define CODE_OP 0

int main(int argc, char** argv) {
    client_t client;
    int val_init = clientInit(&client);
    if (val_init != 0)
        return 1;

    char* host = argv[1];
    char* port = argv[2];
    char* method = obtenerArgumento(argv[3]);
    char* key = obtenerArgumento(argv[4]);
    int val_send = clientSendMessage(&client, host, port, method, key);
    return clientClose(&client, val_send);
}
