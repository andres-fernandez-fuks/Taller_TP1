//
// Created by andres on 8/10/20.
//

#include <stdio.h>

#include "server_main.h"
#include "client_main.h"

int main(int argc,char** argv) {

    char* port;
    unsigned char mensaje[5] = "Andyy";
    if (argc == 5)
        return server_main(argc,argv);
    else
        return client_main(argc,argv);
}


