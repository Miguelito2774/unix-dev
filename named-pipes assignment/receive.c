// receive.c
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

#define PIPE_NAME_1 "/tmp/my_pipe_1"
#define PIPE_NAME_2 "/tmp/my_pipe_2"
#define BUFFER_SIZE 128

int main() {
    mkfifo(PIPE_NAME_1, 0666);  
    mkfifo(PIPE_NAME_2, 0666); 

    char buffer[BUFFER_SIZE];
    int pipe_fd_read = open(PIPE_NAME_1, O_RDONLY);
    int pipe_fd_write = open(PIPE_NAME_2, O_WRONLY);

    while (1) {
        read(pipe_fd_read, buffer, BUFFER_SIZE);
        printf("Received: %s", buffer);
        fgets(buffer, BUFFER_SIZE, stdin);
        write(pipe_fd_write, buffer, strlen(buffer) + 1);
    }

    close(pipe_fd_read);
    close(pipe_fd_write);
    return 0;
}