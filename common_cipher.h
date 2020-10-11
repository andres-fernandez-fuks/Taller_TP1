//
// Created by andres on 10/10/20.
//

#ifndef TP_1_COMMON_CIPHER_H
#define TP_1_COMMON_CIPHER_H


typedef int (*callback_t)(unsigned char* input, size_t len, char* offset_string,
                          unsigned char* buffer, size_t op_type);

typedef struct cipher{
    callback_t cipher_callback;
} cipher_t;

int cipherInit(cipher_t* self, char* method_name);
int cipherCode(cipher_t* self, unsigned char* input, size_t len, char* key,
               unsigned char* buffer);
int cipherDecode(cipher_t* self, unsigned char* input, size_t len, char* key,
                 unsigned char* buffer[]);
int cipherEncoding(cipher_t* self,char* method_name);

#endif //TP_1_COMMON_CIPHER_H
