#include <stdio.h>

int main(int argc, char** argv) {

    FILE* sort_pipe;
    char* chars[5] = {"And", "D", "Bool", "Empty", "Catch"};

    for (int i = 0; i < 5; i++) {
        printf("%s\n", chars[i]);
    }

    char* sort = "/usr/bin/sort";

    sort_pipe = popen(sort, "w");

    for (int i = 0; i < 5; i++) {
        fputs(chars[i], sort_pipe);
        fputc('\n', sort_pipe);
    }

    pclose(sort_pipe);
    
    return 0;
}