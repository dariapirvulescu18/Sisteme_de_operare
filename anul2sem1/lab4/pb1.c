#include <stdio.h>
#include <errno.h>
#include <fcntl.h>

int main(){
    
    pid_t p = fork();
    
    if(p<0)
        return errno;
    else 
        if(p==0){
        
        char * argvs[]= {"ls", "-l", NULL};
        execve("/usr/bin/ls", argvs, NULL);
        perror(NULL);
        //child
        
        }
        
        else{
        wait(NULL);
        printf("%s%d","Child process pid=", p);
        printf("%s%d", "Parent process pid=", getpid());
        //parinte
        }
        
        
     return 0;   
}
