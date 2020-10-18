//
// Created by andres on 17/10/20.
//

#include "common_cipher.h"
#include "client_transmitterSocket.h"

#ifndef TP_1_CLIENT_AUX_H
#define TP_1_CLIENT_AUX_H

int encodeMessage(cipher_t* cipher, unsigned char* input_buf, unsigned char*
encoded_buf, size_t read_bytes, char** argv);
void multiFree(char* arg_1, char* arg_2);
int initializeTransmisionSocket(tSocket_t* socket);
int readEncodeAndSend(cipher_t* cipher, tSocket_t* socket, char** argv);
size_t obtenerInputString(unsigned char* buffer);
int finishClientProgram(cipher_t* cipher, tSocket_t * socket);

#endif //TP_1_CLIENT_AUX_H
