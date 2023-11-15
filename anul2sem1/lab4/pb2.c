#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[]){

    pid_t p = fork();
    
    if(p<0)
        return errno;
    else 
        if(p==0){
        //child process
        int n = atoi(argv[1]);
       
        
        while(n!=1){
            printf("%s%d", "n: ", n);
            if(n%2==0)
                n= n/2;
            
            else
                n=n*3+1;
        }
         printf("%s%d", "n: ", n);
         perror(NULL);
        }
        else {
        
        printf("%s%d","Child process pid=", p);
        printf("%s%d", "Parent process pid=", getpid());
        wait(NULL);
        //parent process
        }

    return 0;
}
