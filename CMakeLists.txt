cmake_minimum_required(VERSION 3.17)
project(TP_1 C)

set(CMAKE_C_STANDARD 99)

add_executable(server server_main.c server.c server.h common_parsing.c common_parsing.h common_cipher.c common_cipher.h common_decoding.c common_decoding.h common_socket.c common_socket.h)

add_executable(client client_main.c client.c client.h common_parsing.c common_parsing.h common_cipher.c common_cipher.h common_decoding.c common_decoding.h common_socket.c common_socket.h)
