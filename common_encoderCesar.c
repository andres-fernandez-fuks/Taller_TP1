//
// Created by andy on 27/10/20.
//

#include <stddef.h>
#include <stdlib.h>
#include "common_encoderCesar.h"

#define TOTAL_CARACTERES 256
#define CODE_OP 0
#define DECODE_OP 1

int cesarEncoderInit(void* self_void, char* key, int op_type) {
    cesarEncoder_t* self = (cesarEncoder_t*) self_void;
    self-> op_type = op_type;
    self-> offset = atoi(key);
    return 0;
}

int cesarEncoderTranslate(void* self_void, unsigned char* buffer, size_t len) {
    cesarEncoder_t* self = (cesarEncoder_t*) self_void;
    for (size_t i = 0; i < len; ++i) {
        if (self->op_type == CODE_OP)
            buffer[i] = (buffer[i] + self->offset)%TOTAL_CARACTERES;
        else
            buffer[i] = (buffer[i] - self->offset)%TOTAL_CARACTERES;
    }
    return 0;
}

int cesarEncoderClose(void* self_void) {
    cesarEncoder_t* self = (cesarEncoder_t*) self_void;
    free(self);
    return 0;
}
