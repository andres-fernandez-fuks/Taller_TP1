//
// Created by andy on 28/10/20.
//

#include <stdlib.h>
#include <string.h>
#include "common_encoderRC4.h"

void rc4Swap(unsigned char* array, unsigned int pos_1, unsigned int pos_2) {
    unsigned char temp = array[pos_1];
    array[pos_1] = array[pos_2];
    array[pos_2] = temp;
}

void rc4InitiateVector(unsigned char* random_array, unsigned char* key,
                       unsigned int key_length) {
    unsigned int i,j;
    for (i = 0; i < 256; ++i)
        random_array[i] = i;

    for (i = j = 0; i < 256; ++i) {
        j = (j + key[i % key_length] + random_array[i]) & 255;
        rc4Swap(random_array, i, j);
    }
}

int rc4CipherInit(void* self_void, char* key, int op_type) {
    rc4Encoder_t* self = (rc4Encoder_t*) self_void;
    self-> key_string = malloc(strlen(key)+1);
    strncpy(self-> key_string, key, strlen(key));
    self-> key_string[strlen(key)] = '\0';
    self-> pos_1 = 0;
    self-> pos_2 = 0;
    self-> op_type = op_type;
    rc4InitiateVector(self->array, (unsigned char*) key, strlen(key));
    return 0;
}

unsigned char rc4Output(rc4Encoder_t* self) {
    self->pos_1 = (self->pos_1+1) & 255;
    self->pos_2 = (self->pos_2 + self->array[self->pos_1]) & 255;
    rc4Swap(self->array, self->pos_1, self->pos_2);
    return self->array[(self->array[self->pos_1]+self->array[self->pos_2])&255];
}

int rc4CipherTranslate(void* self_void, unsigned char* buffer, size_t len) {
    rc4Encoder_t* self = (rc4Encoder_t*) self_void;
    for (size_t i = 0; i < len; ++i) {
        buffer[i] = (unsigned char) buffer[i] ^ rc4Output(self);
    }

    return 0;
}

int rc4CipherClose(void* self_void) {
    rc4Encoder_t* self = (rc4Encoder_t*) self_void;
    free(self->key_string);
    free(self);
    return 0;
}
