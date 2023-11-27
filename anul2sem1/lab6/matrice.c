#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int n = 4;  
int matrice1[4][4];
int matrice2[4][4];
int matrice3[4][4];

typedef struct Args {
    int a;
    int b;
} Args;

void *prod(void *v) {
    Args *vari = (Args *)v;
    int v1 = vari->a;
    int v2 = vari->b;

    int *suma = (int *)malloc(sizeof(int));
    *suma = 0;
    for (int k = 0; k < n; k++) {
        *suma = *suma + matrice1[v1][k] * matrice2[k][v2];
    }
    free(vari);
    pthread_exit(suma);
}

int main() {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            matrice1[i][j] = i+j;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            matrice2[i][j] = i+j+1;
            
//creez o matrice de thread uri

    pthread_t thr[n][n];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            Args *argumente = (Args *)malloc(sizeof(Args));
            argumente->a = i;
            argumente->b = j;
         

            int p = pthread_create(&thr[i][j], NULL, prod, (void *)argumente);
            if (p) {
                perror("pthread_create");
                return errno;
            }
            

        }
        
     for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
        
            void *result;
            int t = pthread_join(thr[i][j], &result);
            if (t) {
                perror("pthread_join");
                return errno;
            }
            matrice3[i][j] = *(int *)result;
            free(result);
        }
        
        


    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d", matrice3[i][j]);
            printf("%s", " ");
        }
        printf("%s", "\n");
    }

    return 0;
}

