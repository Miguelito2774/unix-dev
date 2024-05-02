#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

int main(int argc, char** argv) {
    pid_t child;
    int fd[2];

    char message[50] = "Hello father, I am your child!";
    char read_message[50];

    pipe(fd);

    
    child = fork();
    if(child == 0){
        //Chill process
        printf("Child process!! with pid '%d' and ppid '%d'\n", getpid(), getppid());

        close(fd[0]);
        write(fd[1], message, strlen(message));
        

        printf("Finish child process with pid = '%d' and ppid = '%d'\n", getpid(), getppid());
    } else {
        //Main process
        printf("Main process with pid = %d\n", getpid());

        close(fd[1]);
        read(fd[0], read_message, sizeof(read_message));
        printf("Message from child: %s\n", read_message);

        printf("Finish main process with pid = %d\n", getpid());

    }

    return 0;
}