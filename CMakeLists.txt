cmake_minimum_required(VERSION 3.17)
project(TP_1 C)

set(CMAKE_C_STANDARD 99)

add_executable(TP_1 common_aux_cipher.c common_decoding.c common_decoding.h client_conectarAlSocket.c client_conectarAlSocket.h main.c server_bindearAlSocket.h server_bindearAlSocket.c common_cipher.c common_cipher.h common_aux_cipher.h client_main.c server_main.c client_aux.c client_aux.h server_main.h client_main.h)