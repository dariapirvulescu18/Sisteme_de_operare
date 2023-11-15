#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
int main(int argc, char *argv[] ){
    if(argc < 3){
        printf("Se ruleaza mucp sursa dest\n");
        return -1;
    }    
     printf("argv1=%s, argv2=%s\n", argv[1], argv[2]);
     int hd_sursa = open(argv[1], O_RDONLY);
     int hd_dest = open(argv[2],O_CREAT | O_TRUNC | O_WRONLY, 0666);
     char buf[20];
     int r = read(hd_sursa, buf, 20 );
     while(r > 0)
     {  
        write(hd_dest, buf, r);
        r = read(hd_sursa, buf, 20);
        
     } 
      close(hd_sursa);
      close(hd_dest);
     return 0;
}
