#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[]){


    pid_t p[100];
    printf("%s%d", "Starting parent",getpid());
    
    for(int i=1; i<argc; i++){
     p[i]= fork();
     if(p[i]<0)
        return errno;
    else 
        if(p[i]==0){
            int n= atoi(argv[i]);
            printf("%d%s", n, ":");
             while(n!=1){
                 printf("%s%d", "n: ", n);
                 if(n%2==0)
                    n= n/2;
            
                else
                     n=n*3+1;
                     }
        }
            printf("%d.\n", 1);
            printf("%s%d","Done parent", getppid());
            printf("%s%d", "Me: ", getpid());
            exit(0);
            perror(NULL);
     }
    for (int i=1; i<=argc; i++)
        if (p[i])
            wait(NULL);
    
    
    
    return 0;
}
   
