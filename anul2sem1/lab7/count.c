#include <pthread.h>
#include <stdio.h>
#include <errno.h>

#define MAX_RESOURCES 5
int available_resources = MAX_RESOURCES ;
pthread_mutex_t mutex;

int decrease_count(int count){
        pthread_mutex_lock(&mutex);
        if(available_resources < count){
            pthread_mutex_unlock(&mutex);
                return -1;
        }
        else 
            available_resources -=count;
        pthread_mutex_unlock(&mutex);    
        return 0;
}

int increase_count(int count){
     pthread_mutex_lock(&mutex);
     available_resources+=count;
     pthread_mutex_unlock(&mutex);
     return 0;
}

void * functie (void * v){
    int value = *((int*) v);

    
    if (decrease_count(value) == 0) {
        printf("Got %d resources %d remaining\n", value, available_resources);
        increase_count(value);
        printf("Released %d resources %d remaining\n", value, available_resources);
    } else {
        printf("Not enough resources for %d\n", value);
    }
    return NULL;
}

int main(){

    pthread_t threads [4];
    int resource_thread1 =2;
    int resource_thread2 =2;
    int resource_thread3 =1;
    
    if(pthread_mutex_init(&mutex,NULL)){
        perror(NULL);
        return errno;
    }
    
    printf("MAX_RESOURCES = %d\n", available_resources);
    
   
    int p1 = pthread_create(&threads[1], NULL, functie, &resource_thread1);
    if (p1) {
        perror("pthread_create");
        return errno;
    }
    int p2 = pthread_create(&threads[2], NULL, functie, &resource_thread2);
    if (p2) {
        perror("pthread_create");
        return errno;
    }
    int p3 = pthread_create(&threads[3], NULL, functie, &resource_thread3);
    if (p3) {
        perror("pthread_create");
        return errno;
    }
    
    pthread_join(threads[1], NULL);
    pthread_join(threads[2], NULL);
    pthread_join(threads[3], NULL);
    
    pthread_mutex_destroy(&mutex);
    
    
return 0;
}
