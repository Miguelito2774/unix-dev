#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

void printProcessInfo(const char* processName, int counter) {
    printf("%s process PID(%d), PPID(%d), counter at %d\n", processName, getpid(), getppid(), counter);
}

void processP1() {
    int counter = 0;
    while (counter <= 10) {
        printProcessInfo("Main", counter);
        sleep(1);
        counter++;
    }
    printf("Main process finished.\n");
}

void processP2() {
    int counter = 10;
    while (counter <= 20) {
        printProcessInfo("Child", counter);
        sleep(1);
        counter++;
    }
    printf("Child process finished.\n");
}

void processP3() {
    int counter = 20;
    while (counter <= 40) {
        printProcessInfo("Child of Child", counter);
        sleep(1);
        counter += 2;
    }
    printf("Child of Child process finished.\n");
}

int main() {
    pid_t p1, p2, p3;

    p1 = fork();
    if (p1 == 0) {
        // Child process (P1)
        processP1();
        return 0;
    }

    p2 = fork();
    if (p2 == 0) {
        // Child process (P2)
        processP2();
        p3 = fork();
        if (p3 == 0) {
            // Child of child process (P3)
            processP3();
            return 0;
        }
        wait(NULL); // Wait for P3 to finish
        return 0;
    }

    wait(NULL); // Wait for P2 to finish
    printf("Parent process finished.\n");

    return 0;
}