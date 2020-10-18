//
// Created by andres on 17/10/20.
//

#ifndef TP_1_SERVER_AUX_H
#define TP_1_SERVER_AUX_H

#include <stdbool.h>
#include "common_cipher.h"
#include "common_socket.h"
#include "common_cipher_aux.h"


int decode(cipher_t* cipher, unsigned char* coded_buffer, unsigned char*
decoded_buffer, size_t read_bytes, char** argv);
int receiveDecodeAndPrint(cipher_t* cipher, socket_t* socket, char** argv,
                          bool* shouldBreak);
void printOutput(unsigned char* cadena_encriptada, size_t largo_cadena);

#endif //TP_1_SERVER_AUX_H
