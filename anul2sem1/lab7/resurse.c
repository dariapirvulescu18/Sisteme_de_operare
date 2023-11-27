#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_RESOURCES 5

int available_resources = MAX_RESOURCES;
pthread_mutex_t mutex;

int decrease_count(int count) {
    pthread_mutex_lock(&mutex);

    if (available_resources < count) {
        pthread_mutex_unlock(&mutex);
        return -1;
    } 
    else {
        available_resources -= count;
    }

    pthread_mutex_unlock(&mutex);
    return 0;
}

int increase_count(int count) {
    pthread_mutex_lock(&mutex);

    available_resources += count;

    pthread_mutex_unlock(&mutex);
    return 0;
}

void* thread_function(void* arg) {
    int requested_resources = *((int*)arg);

    if (decrease_count(requested_resources) == 0) {
        printf("Got %d resources %d remaining\n", requested_resources, available_resources);
        increase_count(requested_resources);
        printf("Released %d resources %d remaining\n", requested_resources, available_resources);
    } else {
        printf("Not enough resources for %d\n", requested_resources);
    }

    return NULL;
}

int main() {
    pthread_t threads[3];
    int thread1_resources = 2;
    int thread2_resources = 2;
    int thread3_resources = 1;

    pthread_mutex_init(&mutex, NULL);

    printf("MAX_RESOURCES = %d\n", MAX_RESOURCES);

    pthread_create(&threads[0], NULL, thread_function, &thread1_resources);
    pthread_create(&threads[1], NULL, thread_function, &thread2_resources);
    pthread_create(&threads[2], NULL, thread_function, &thread3_resources);

    pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);
    pthread_join(threads[2], NULL);

    pthread_mutex_destroy(&mutex);

    return 0;
}

