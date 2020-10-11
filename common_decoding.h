//
// Created by andres on 7/10/20.
//

#ifndef TP_1_COMMON_DECODING_H
#define TP_1_COMMON_DECODING_H

int cesar_encoding(unsigned char* input, size_t len, char* offset_string,
                 unsigned char* buffer, size_t op_type) ;

int vigenere_encoding(unsigned char* input, size_t len, char* offset_string,
                 unsigned char* buffer, size_t op_type);

int rc4_encoding(unsigned char* input, size_t len, char* offset_string,
                 unsigned char* buffer, size_t op_type);

#endif //TP_1_COMMON_DECODING_H
