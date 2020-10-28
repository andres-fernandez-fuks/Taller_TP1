//
// Created by andres on 10/10/20.
//

#include "common_encoderCesar.h"
#include "common_encoderVigenere.h"
#include "common_encoderRC4.h"

#ifndef TP_1_COMMON_CIPHER_H
#define TP_1_COMMON_CIPHER_H

typedef int (*init_callback_t)(void* cipher, char* key, int op_type);
typedef int (*translate_callback_t)(void* cipher, unsigned char* input,
        size_t len);
typedef int (*close_callback_t)(void* cipher);

typedef struct cipher{
    init_callback_t init_callback;
    translate_callback_t translate_callback;
    close_callback_t close_callback;
    void* encoder;
} cipher_t;

int cipherInit(cipher_t* self, char* method_name, char* key, int op_type);
int cipherClose(cipher_t* self);
int cipherTranslate(cipher_t* self, unsigned char* buffer, size_t len);

#endif //TP_1_COMMON_CIPHER_H
