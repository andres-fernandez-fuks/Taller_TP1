//
// Created by andres on 10/10/20.
//

#include <limits.h>
#include <stdio.h>
#include "server_bindearAlSocket.h"
#include "server_main.h"
#include "common_aux_cipher.h"

#define DECODE_OP 1

int server_main(int argc, char** argv) {
    char* port = argv[2];
    char coded_buffer[PATH_MAX] = {0};
    size_t bytes_leidos = 0;
    bindearAlSocket(port,coded_buffer,&bytes_leidos);
    if (!bytes_leidos)
        return 1;
    //imprimir_cadena(coded_buffer,bytes_leidos,"%d");
    char decoded_buffer[bytes_leidos];
    char* method_name = obtener_argumento(argv[3]);
    char* key_string = obtener_argumento(argv[4]);
    puts("Deoodificando mensaje...");
    int decod_ok = stringEncode(coded_buffer, decoded_buffer, bytes_leidos, method_name,
                 key_string, DECODE_OP);
    if (decod_ok != 0)
        return 1;
    printf("Mensaje decodificado: ");
    imprimir_cadena(decoded_buffer,bytes_leidos,"%c");
}