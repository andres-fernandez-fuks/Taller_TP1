//
// Created by andres on 7/10/20.
//
#include <stddef.h>

#ifndef TP_1_COMMON_DECODING_H
#define TP_1_COMMON_DECODING_H

void rc4InitiateVector(unsigned char* random_array, unsigned char* key,
                       unsigned int key_length);
int rc4Encoding(unsigned char* input, size_t len, unsigned char* buffer,
                void** extra);
int vigenereEncoding(unsigned char* input, size_t len, unsigned char* buffer,
                     void** extra);
int cesarEncoding(unsigned char* input, size_t len, unsigned char* buffer,
                  void** extra);

#endif //TP_1_COMMON_DECODING_H
