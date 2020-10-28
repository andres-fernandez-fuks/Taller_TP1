//
// Created by andy on 28/10/20.
//

#ifndef TP_1_COMMON_ENCODERRC4_H
#define TP_1_COMMON_ENCODERRC4_H

typedef struct rc4Encoder{
	// cppcheck-suppress unusedStructMember
    char* key_string;
    // cppcheck-suppress unusedStructMember
    int op_type;
    // cppcheck-suppress unusedStructMember
    int pos_1;
    // cppcheck-suppress unusedStructMember
    int pos_2;
    // cppcheck-suppress unusedStructMember
    unsigned char array[256];
} rc4Encoder_t;

int rc4CipherInit(void* self_void, char* key, int op_type);
int rc4CipherTranslate(void* self_void, unsigned char* input, size_t len);
int rc4CipherClose(void* self_void);

#endif //TP_1_COMMON_ENCODERRC4_H
