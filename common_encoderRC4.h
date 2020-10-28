//
// Created by andy on 28/10/20.
//

#ifndef TP_1_COMMON_ENCODERRC4_H
#define TP_1_COMMON_ENCODERRC4_H

// el uso de las líneas para suprimir cppcheck está justificado en la sección
// de comentarios del informe

typedef struct rc4Encoder{
	// cppcheck-suppress unusedStructMember
    char* key_string;
    // cppcheck-suppress unusedStructMember
    int pos_1;
    // cppcheck-suppress unusedStructMember
    int pos_2;
    // cppcheck-suppress unusedStructMember
    unsigned char array[256];
} rc4Encoder_t;

int rc4EncoderInit(void* self_void, char* key, int op_type);
int rc4EncoderTranslate(void* self_void, unsigned char* buffer, size_t len);
int rc4EncoderClose(void* self_void);

#endif //TP_1_COMMON_ENCODERRC4_H
