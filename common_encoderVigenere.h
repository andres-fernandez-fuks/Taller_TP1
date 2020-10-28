//
// Created by andy on 27/10/20.
//

#ifndef TP_1_COMMON_ENCODERVIGENERE_H
#define TP_1_COMMON_ENCODERVIGENERE_H

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

int vigenereCipherInit(void* self_void, char* key, int op_type);
int vigenereCipherTranslate(void* self_void, unsigned char* buffer, size_t len);
int vigenereCipherClose(void* self_void);

#endif //TP_1_COMMON_ENCODERVIGENERE_H
