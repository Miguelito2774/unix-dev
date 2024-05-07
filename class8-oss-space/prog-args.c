#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    printf("arg: %d\n", argc);

    for (int i = 0; i < argc; i++) {
        printf("argv[%d]: %s\n", i, argv[i]);
    }

    if (argc != 3) {
        printf("Invalid number of arguments\n");
        printf("Usage:\n\t./prog -p <port>\n");
        return 1;
    }

    if (strcmp(argv[1], "-p") != 0) {
        printf("Unknow argument: %s\n", argv[1]);
        return 1;
    }

    int port = atoi(argv[2]);
    if (port == 0){
        printf("Invalid port number: %s\n", argv[2]);
        return 1;
    }

    if (port < 1000 || port > 65535) {
        printf("Invalid port, it should be between 1000 and 65535\n");
        return 1;
    }

    printf("Running on port %d\n", port);


    return 0;