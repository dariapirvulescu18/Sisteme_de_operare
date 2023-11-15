#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void *hello(void *v) {
    char *input = (char *)v;
    int lungime = strlen(input);
    
    char *output = (char *)malloc(lungime + 1);
    
    if (output == NULL) {
        perror("malloc");
        pthread_exit(NULL);
    }

    for (int i = 0; i < lungime; i++)
        output[i] = input[lungime - i - 1];

    output[lungime] = '\0';

    pthread_exit(output);
}

int main(int argc, char *argv[]) {
    pthread_t thr;

    int p = pthread_create(&thr, NULL, hello, (void *)argv[1]);
    if (p) {
        perror("pthread_create");
        return errno;
    }

    void *result;
    int t = pthread_join(thr, &result);
    if (t) {
        perror("pthread_join");
        return errno;
    }

    printf("Sirul rasturnat este: %s\n", (char *)result);
    free(result);

    return 0;
}

