#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

int main(int argc, char *argv[]) {
    pid_t p[100];
    printf("%s%d\n", "Starting parent ", getpid());

    char shm_name[] = "myshm";
    int shm_fd;
    shm_fd = shm_open(shm_name, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);

    if (shm_fd < 0) {
        perror(NULL);
        return errno;
    }

    size_t shm_size = 4096 * argc;

    if (ftruncate(shm_fd, shm_size) == -1) {
        perror(NULL);
        shm_unlink(shm_name);
        return errno;
    }

    for (int i = 1; i < argc; i++) {
        p[i] = fork();
        if (p[i] < 0) {
            return errno;
        } else if (p[i] == 0) {
            int *shm_ptr = mmap(0, 4096, PROT_WRITE, MAP_SHARED, shm_fd, (i - 1) * 4096);

            if (shm_ptr == MAP_FAILED) {
                perror(NULL);
                shm_unlink(shm_name);
                return errno;
            }

            int n = atoi(argv[i]);
            printf("%d%s", n, ":");
            int j = 0;

            while (n != 1) {
                shm_ptr[j] = n;
                if (n % 2 == 0)
                    n = n / 2;
                else
                    n = n * 3 + 1;
                j++;
            }
            shm_ptr[j] = 1;
            munmap(shm_ptr, 4096);
            exit(0);
        }
    }

    for (int i = 1; i < argc; i++) {
        if (p[i]) {
            wait(NULL);
        }
    }

    int i = 0;
    while (i < argc - 1) {
        printf("%d: ", atoi(argv[i + 1]));
        int *shm_ptr = mmap(0, 4096, PROT_READ, MAP_SHARED, shm_fd, i * 4096);
        int j = 0;
        while (shm_ptr[j] != 1) {
            printf("%d ", shm_ptr[j]);
            j++;
        }
        printf("1\n");
        munmap(shm_ptr, 4096);
        i++;
    }

    shm_unlink(shm_name);

    return 0;
}

