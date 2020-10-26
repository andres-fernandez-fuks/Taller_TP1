//
// Created by andres on 17/10/20.
//

#ifndef TP_1_SERVER_H
#define TP_1_SERVER_H

#include <stdbool.h>
#include "common_cipher.h"
#include "common_socket.h"

#define CHUNK_SIZE 64

typedef struct server{
    cipher_t cipher;
    socket_t connection_socket;
    socket_t acceptance_socket;
    unsigned char buffer[CHUNK_SIZE];
} server_t;


int decode(cipher_t* cipher, unsigned char* coded_buffer, unsigned char*
decoded_buffer, size_t read_bytes, char** argv);
int receiveDecodeAndPrint(cipher_t* cipher, socket_t* socket, char** argv,
                          bool* shouldBreak);
void printOutput(unsigned char* cadena_encriptada, size_t largo_cadena);
int initializeServer(server_t* self);
int serverEstablishConnection(server_t* self, char* port);
int finishServerProgram(server_t* server, int ret_value);
int serverReceiveMessage(server_t* server, char* method_name, char* key);

#endif //TP_1_SERVER_H
