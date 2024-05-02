#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int g_v = 0;
pthread_mutex_t gv_mutex;

void* do_increment_work(int* count) {
    printf("count: %d\n", *count);
    *count = *count + 1;
    pthread_t t_id = pthread_self();
    printf("thread[%lu] - ... doing increment work...\n", t_id);
    // lock
    pthread_mutex_lock(&gv_mutex);
    g_v++;
     printf("thread[%lu] - ... inc: g_v[%d].\n", t_id, g_v);
    // unlock
    pthread_mutex_unlock(&gv_mutex);
    printf("thread[%lu] - ... increment finished\n", t_id);
}


void* do_decrement_work() {
    pthread_t t_id = pthread_self();
    printf("thread[%lu] - ... doing decrement work...\n", t_id);
    // lock
    pthread_mutex_lock(&gv_mutex);
    g_v--;
    printf("thread[%lu] - ... dec: g_v[%d].\n", t_id, g_v);
    // unlock
    pthread_mutex_unlock(&gv_mutex);
    printf("thread[%lu] - ... decrement finished\n", t_id);
}

int main(int argc, char** argv) {
    
    int threads = 8;
    int count = 0;
    pthread_t inc_thread_ids[threads], dec_thread_ids[threads];
    pthread_mutex_init(&gv_mutex, NULL);

    for (int i = 0; i < threads; i++) {
        int t_status = pthread_create(&inc_thread_ids[i], NULL, do_increment_work, (void *)&count);

        if (t_status == -1) {
            perror("Error creating inc thread.");
            return 1;
        }
    }

    for (int i = 0; i < threads; i++) {
        int join_status = pthread_join(inc_thread_ids[i], NULL);

        if (join_status == -1) {
            perror("Error joining inc thread.");
            return 2;
        }
    }

    //Decrement threads
    for (int i = 0; i < threads; i++) {
        int t_status = pthread_create(&dec_thread_ids[i], NULL, do_decrement_work, NULL);

        if (t_status == -1) {
            perror("Error creating dec thread.");
            return 1;
        }
    }

    for (int i = 0; i < threads; i++) {
        int join_status = pthread_join(dec_thread_ids[i], NULL);

        if (join_status == -1) {
            perror("Error joining dec thread.");
            return 2;
        }
    }

    pthread_mutex_destroy(&gv_mutex);
    printf("Finishing main\n");

    return 0;
}