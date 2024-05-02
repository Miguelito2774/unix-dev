#include <stdlib.h>
#include <sys/shm.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char** argv) {

    int shm_id;
    void* shm_ptr;

    shm_id = shmget((key_t)4583, 2048, 0666);

    shm_ptr = shmat(shm_id, NULL, 0);

    printf("Message read from shared memory: %s\n", (char*)shm_ptr);

    return 0;
}