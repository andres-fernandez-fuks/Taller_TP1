//
// Created by andres on 10/10/20.
//

#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include "common_cipher.h"
#include "common_decoding.h"

#define CODE_OP 0
#define DECODE_OP 1
#define CESAR_TYPE 1
#define VIGENERE_TYPE 2
#define RC4_TYPE 3

int cesar_init(cipher_t* self);
int vigenere_init(cipher_t* self);
int rc4Init(cipher_t* self);
void** assembleExtraVector(cipher_t* self);

int cipherInit(cipher_t* self, char* method_name, char* key, int op_type) {
    self-> op_type = op_type;
    self-> key_string = malloc(strlen(key)+1);
    strncpy(self->key_string, key, strlen(key));
    self->key_string[strlen(key)] = '\0';
    return cipherEncoding(self, method_name);
}

int cipherTranslate(cipher_t* self, unsigned char* input, size_t len,
                    unsigned char* buffer) {
    void** extra = assembleExtraVector(self);
    if (!extra)
        return 1;
    int val_encoding = self->decoding_function(input, len, self->key_string,
                                               buffer, extra);
    free(extra);
    return val_encoding;
}

int cipherEncoding(cipher_t* self, char* method_name) {
    if (strcmp(method_name,"cesar") == 0)
        return cesar_init(self);
    else if (strcmp(method_name,"vigenere") == 0)
        return vigenere_init(self);
    else if (strcmp(method_name,"rc4") == 0)
        return rc4Init(self);
    return 1;
}

int cipherDestroy(cipher_t* self) {
    free(self->key_string);
    return 0;
}

int cesar_init(cipher_t* self) {
    self-> decoding_function = &cesar_encoding;
    self-> type = CESAR_TYPE;
    return 0;
}

int vigenere_init(cipher_t* self) {
    self->decoding_function = &vigenere_encoding;
    self->count = 0;
    self-> type = VIGENERE_TYPE;
    return 0;
}

int rc4Init(cipher_t* self) {
    self->decoding_function = &rc4_encoding;
    self-> type = RC4_TYPE;
    self-> count = 0;
    self-> rc4_pos2 = 0;
    memset(self->rc4_array, 0, sizeof(self->rc4_array));
    rc4_init(self->rc4_array, (unsigned char*) self-> key_string,
        strlen(self->key_string));
    return 0;
}

void** cesarVector(cipher_t* self) {
    void** extra = malloc(sizeof(void*));
    if (!extra)
        return NULL;
    extra[0] = (void*) &self->op_type;
    return extra;
}

void** vigenereVector(cipher_t* self) {
    void** extra = malloc(2*sizeof(void*));
    if (!extra)
        return NULL;
    extra[0] = (void*) &self->op_type;
    extra[1] = (void*) &self->count;
    return extra;
}

void** rc4Vector(cipher_t* self) {
    void ** extra = malloc(3*sizeof(void*));
    if (!extra)
        return NULL;
    extra[0] = (void*) self->rc4_array;
    extra[1] = (void*) &self->count;
    extra[2] = (void*) &self->rc4_pos2;
    return extra;
}

void** assembleExtraVector(cipher_t* self) {
    switch (self->type) {
        case CESAR_TYPE:
            return cesarVector(self);
        case VIGENERE_TYPE:
            return vigenereVector(self);
        case RC4_TYPE:
            return rc4Vector(self);
    }
    return NULL;
}
