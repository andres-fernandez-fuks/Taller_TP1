//
// Created by andres on 17/10/20.
//

#include "common_cipher.h"
#include "common_socket.h"
#include "common_cipher_aux.h"

#ifndef TP_1_CLIENT_AUX_H
#define TP_1_CLIENT_AUX_H

int encodeMessage(cipher_t* cipher, unsigned char* input_buf, unsigned char*
encoded_buf, size_t read_bytes, char** argv);
void multiFree(char* arg_1, char* arg_2);
int readEncodeAndSend(cipher_t* cipher, socket_t* socket, char** argv);
size_t obtenerInputString(unsigned char* buffer);

#endif //TP_1_CLIENT_AUX_H
