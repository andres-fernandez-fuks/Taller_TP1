//
// Created by andy on 27/10/20.
//

#ifndef TP_1_COMMON_ENCODERVIGENERE_H
#define TP_1_COMMON_ENCODERVIGENERE_H

// el uso de las líneas para suprimir cppcheck está justificado en la sección
// de comentarios del informe

typedef struct vigenereEncoder{
    // cppcheck-suppress unusedStructMember	
    char* key_string;
    // cppcheck-suppress unusedStructMember
    size_t key_length;
    // cppcheck-suppress unusedStructMember
    int last_pos;
    // cppcheck-suppress unusedStructMember
    int op_type;
} vigenereEncoder_t;

int vigenereEncoderInit(void* self_void, char* key, int op_type);
int vigenereEncoderTranslate(void* self_void, unsigned char* buffer,
	size_t len);
int vigenereEncoderClose(void* self_void);

#endif //TP_1_COMMON_ENCODERVIGENERE_H
