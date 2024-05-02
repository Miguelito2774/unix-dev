#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>


int main (int argc, char** argv) {
    char* f_open = "files.c";

    int fd = open(f_open, O_RDONLY);
    printf("fd = %d\n", fd);


    char content[10];
    int size_read = read(fd, content, 10);
    printf("content = %s\n", content);
    printf("size_read = %d\n", size_read);

    char mod[3] = {'A', 'B', 'C'};
    int size_write = write(fd, mod, 3);
    printf("size_write = %d\n", size_write);

    int fd_write = open("write-me.txt", O_WRONLY | O_CREAT, 0666);
    printf("fd_write = %d\n", fd_write);
    size_write = write(fd_write, mod, 3);
    printf("size_write = %d\n", size_write);

    //Now lets read the file
    int fd_read = read(fd_write, content, 3);
    printf("content = %s\n", content);



    
    return 0;
}