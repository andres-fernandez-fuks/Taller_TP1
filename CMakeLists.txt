cmake_minimum_required(VERSION 3.17)
project(TP_1 C)

set(CMAKE_C_STANDARD 99)

add_executable(client common_aux_cipher.c common_decoding.c common_decoding.h client_connectToSocket.c client_connectToSocket.h common_cipher.c common_cipher.h common_aux_cipher.h client_main.c client_aux.c client_aux.h client_main.h)

add_executable(server common_aux_cipher.c common_decoding.c common_decoding.h server_bindToSocket.h server_bindToSocket.c common_cipher.c common_cipher.h common_aux_cipher.h server_main.c server_main.h)