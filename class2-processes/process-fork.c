#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

//PID: Process ID(Unique identifier for a process)

int main(int argc, char** argv) {

    pid_t main_pid = getpid();
    pid_t p_main_pid = getppid();

    printf("main_pid = %d\n", main_pid);
    printf("p_main_pid = %d\n", p_main_pid);

    pid_t child = fork();

    if (child == 0){
        // Child process
        printf("child pid = %d, ppid = %d\n", getpid(), getppid());
        sleep(5);
        printf("child finish\n");
        exit(0); // Homework: What another exit codes are apart of 0? 
    } else {
        // Parent process
        printf("main pid = %d, ppid = %d\n", getpid(), getppid());
        wait(NULL); // Homework: What another functions can be used instead of wait?
        printf("main finish\n");
    }

    return 0;
}

// Homework for Thursday
// Three levels of process
// p1 -> p2 -> p3
// p1 -> print pid, parent pid and counter every second until 10
// p2 -> print pid, parent pid and counter every second starting from 10 until 20
// p3 -> print pid, parent pid and counter every second starting from 20 until 40
// p2 needs to wait for p3 to finish