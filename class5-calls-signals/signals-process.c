#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>

int main (int argc, char** argv) {

    int child_pid = fork();

    if (child_pid == 0) {
        //Child
        int counter = 0;
        while(1){
            printf("Child: %d\n", counter++);
            sleep(1);
        }
    } else {
        //Main
        sleep(6);
        kill(child_pid, SIGKILL);
        wait(NULL);
    }

    return 0;

}