#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
int main(){
    int nwrite = write(1,"Hello World!\n", 13);
    if(nwrite < 0){
        perror ("read buf");
        return errno;
    }
        
}
