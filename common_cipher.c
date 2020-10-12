//
// Created by andres on 10/10/20.
//

#include <stddef.h>
#include <string.h>
#include "common_cipher.h"
#include "common_decoding.h"

#define CODE_OP 0
#define DECODE_OP 1

int cipherInit(cipher_t* self, char* method_name) {
    return cipherEncoding(self, method_name);
}

int cipherCode(cipher_t* self, unsigned char* input, size_t len, char* key,
               unsigned char* buffer) {
    return self->cipher_callback(input, len, key,buffer, CODE_OP);
}

int cipherDecode(cipher_t* self, unsigned char* input, size_t len, char* key,
                 unsigned char* buffer) {
    return self->cipher_callback(input, len, key, buffer, DECODE_OP);
}

int cipherEncoding(cipher_t* self, char* method_name) {
    callback_t function = NULL;
    if (strcmp(method_name,"cesar") == 0)
        function = &cesar_encoding;
    else if (strcmp(method_name,"vigenere") == 0)
        function = &vigenere_encoding;
    else if (strcmp(method_name,"rc4") == 0)
        function = &rc4_encoding;
    if (!function)
        return 1;
    self->cipher_callback = function;
    return 0;

}
