#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#define MESSAGE_SIZE 128

int main(int argc, char** argv) {

    void* mmap_ptr;
    int fd = open("/tmp/shared_resource", O_RDWR, 0666);


    mmap_ptr = mmap(NULL, MESSAGE_SIZE, 
          PROT_WRITE | PROT_READ, MAP_SHARED, fd, 0);
    
    /*if (mmap_ptr == -1) {
        perror("Error getting mmap\n");
        exit(1);
    }
    */

    printf("mmap_ptr: %d\n", mmap_ptr);

    char msg[64];
    memcpy(msg, mmap_ptr, 64);
    printf("Message read from mmap: %s\n", msg);

    return 0;

}