//
// Created by andres on 7/10/20.
//

#ifndef TP_1_COMMON_DECODING_H
#define TP_1_COMMON_DECODING_H

void rc4_init(unsigned char* arreglo_random, unsigned char* key, unsigned int
        key_length);
int rc4_encoding(unsigned char* input, size_t len, char* key_string, unsigned
        char* buffer, void** extra);
int vigenere_encoding(unsigned char* input, size_t len, char* key_string,
                      unsigned char* buffer, void** extra);
int cesar_encoding(unsigned char* input, size_t len, char* offset_string,
                   unsigned char* buffer, void** extra);

#endif //TP_1_COMMON_DECODING_H
