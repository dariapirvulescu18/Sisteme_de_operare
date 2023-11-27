#include <pthread.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <semaphore.h>

#define MAX_RESOURCES 5
int available_resources = MAX_RESOURCES ;

pthread_mutex_t mutex;
sem_t barrier_sem;
int count = 0;
int N;
void init_barrier() {
    pthread_mutex_init(&mutex, NULL);
    sem_init(&barrier_sem, 0, 0);
    count = 0;
     N=5;   
}

void barrier_point(){
    pthread_mutex_lock(&mutex);
    count = count + 1;
    
   
    if(count == N){
        for(int i = 0; i < N - 1; i++)
            sem_post(&barrier_sem);
    }
    else{
     pthread_mutex_unlock(&mutex);
     sem_wait(&barrier_sem);
    }
   
    
}

void *tfun(void *v){
    int *tid = (int *)v;
    printf("%d reached the barrier\n", *tid);
    barrier_point();
    printf("%d passed the barrier\n", *tid);
    return NULL;
}

int main(){
    pthread_t threads[5];

    init_barrier();
    int thread_resources[5] = {1, 2, 3, 4, 5};

    for(int i = 0; i < 5; i++){
        pthread_create(&threads[i], NULL, tfun, &thread_resources[i]);
    }

    for(int i = 0; i < 5; i++){
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    sem_destroy(&barrier_sem);
    return 0;
}

