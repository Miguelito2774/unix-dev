#include <stdio.h>
#include <unistd.h>

//Process 

int main(int argc, char** argv) {
    
    for(int i = 0; i < 10; i++){
        printf("i = %d\n", i);
        sleep(1);
    }

    return 0;
}

