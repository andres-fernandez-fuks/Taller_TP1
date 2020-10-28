//
// Created by andy on 27/10/20.
//

#include <stdlib.h>

#ifndef TP_1_COMMON_CIPHERCESAR_H
#define TP_1_COMMON_CIPHERCESAR_H

typedef struct cesarEncoder{
    // cppcheck-suppress unusedStructMember	
    int offset;
    // cppcheck-suppress unusedStructMember    
    int op_type;
} cesarEncoder_t;

int cesarCipherInit(void* self_void, char* key, int op_type);
int cesarCipherTranslate(void* self_void, unsigned char* buffer, size_t len);
int cesarCipherClose(void* self_void);

#endif //TP_1_COMMON_CIPHERCESAR_H
