//
// Created by andy on 27/10/20.
//

#include <stdlib.h>

#ifndef TP_1_COMMON_CIPHERCESAR_H
#define TP_1_COMMON_CIPHERCESAR_H

// el uso de las líneas para suprimir cppcheck está justificado en la sección
// de comentarios del informe

typedef struct cesarEncoder{
    // cppcheck-suppress unusedStructMember	
    int offset;
    // cppcheck-suppress unusedStructMember    
    int op_type;
} cesarEncoder_t;

int cesarEncoderInit(void* self_void, char* key, int op_type);
int cesarEncoderTranslate(void* self_void, unsigned char* buffer, size_t len);
int cesarEncoderClose(void* self_void);

#endif //TP_1_COMMON_CIPHERCESAR_H
