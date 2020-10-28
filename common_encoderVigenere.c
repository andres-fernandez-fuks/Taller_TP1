//
// Created by andy on 27/10/20.
//

#include <stdlib.h>
#include <string.h>
#include "common_encoderVigenere.h"

#define CODE_OP 0
#define DECODE_OP 1


int vigenereEncoderInit(void* self_void, char* key, int op_type) {
    vigenereEncoder_t* self = (vigenereEncoder_t*) self_void;
    self-> key_string = malloc(strlen(key)+1);
    strncpy(self-> key_string, key, strlen(key));
    self-> key_string[strlen(key)] = '\0';
    self-> last_pos = 0;
    self-> key_length = strlen(key);
    self-> op_type = op_type;
    return 0;
}

int vigenereEncoderTranslate(void* self_void, unsigned char* buffer,
    size_t len){
    vigenereEncoder_t* self = (vigenereEncoder_t*) self_void;
    for (size_t i = 0; i < len; i++) {
        int pos_clave = (i+self->last_pos) % self->key_length;
        if (self->op_type == CODE_OP)
            buffer[i] = (buffer[i] + self->key_string[pos_clave])%256;
        else
            buffer[i] = (buffer[i] - self->key_string[pos_clave])%256;
    }
    self->last_pos += len;
    return 0;
}

int vigenereEncoderClose(void* self_void) {
    vigenereEncoder_t* self = (vigenereEncoder_t*) self_void;
    if (!self)
        return 1;
    if (!self->key_string)
        return 1;
    free(self->key_string);
    free(self);
    return 0;
}


