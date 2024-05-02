#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void* do_work(void* arg) {
    pthread_t t_id = pthread_self();
    printf("thread[%lu] - ... doing work...\n", t_id);
    sleep(1);
    printf("thread[%lu] - ... finished\n", t_id);

}

int main(int argc, char** argv) {
    
    int threads = 8;
    pthread_t thread_ids[threads];

    for (int i = 0; i < threads; i++) {
        int t_status = pthread_create(&thread_ids[i], NULL, do_work, NULL);

        if (t_status == -1) {
            perror("Error creating thread");
            return 1;
        }
    }

    for (int i = 0; i < threads; i++) {
        int join_status = pthread_join(thread_ids[i], NULL);

        if (join_status == -1) {
            perror("Error joining thread");
            return 2;
        }
    }

    printf("Finishing main\n");

    return 0;
}
