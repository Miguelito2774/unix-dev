#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>

void sigkill_handler(int signal){
    printf("SIGKILL handling\n");
}

void sigstop_handler(int signal){
    printf("SIGSTOP handling\n");
}

void sigcont_handler(int signal){
    printf("SIGCONT handling\n");
}

void sigint_handler(int signal){
    printf("SIGINT handling\n");
    exit(0);
}

int main (int argc, char** argv) {

    int child_pid = fork();

    signal(SIGINT, &sigint_handler);

    if (child_pid == 0) {
        //Child
        signal(SIGKILL, &sigkill_handler);
        signal(SIGSTOP, &sigstop_handler);
        signal(SIGCONT, &sigcont_handler);
        int counter = 0;
        while(1){
            printf("Child: %d\n", counter++);
            sleep(1);
        }
    } else {
        //Main
        sleep(6);
        kill(child_pid, SIGSTOP);
        sleep(6);
        kill(child_pid, SIGCONT);
        sleep(6);
        kill(child_pid, SIGKILL);
        wait(NULL);
    }

    return 0;

}