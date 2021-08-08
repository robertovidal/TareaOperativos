#include <sys/types.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>
int main(int argc, char *argv[]){
    int n;
    int pid;
    int shm_fd;
    void *ptrwrite;
    void *ptrread;
    char string_number[10];
    if(argc == 1)
        printf("The number is missing\n");
    if(argc == 2){
        int length = strlen(argv[1]);
        int isNumber = 1;
        for(int i = 0; i < length; i++){
            if(!isdigit(argv[1][i]))
                isNumber = 0;
        }
        if(!isNumber)
            printf("The input is not a number\n");
        else{
            shm_fd = shm_open("Collatz", O_CREAT | O_RDWR, 0666);
            ftruncate(shm_fd, 4096);
            ptrwrite = mmap(0, 4096, PROT_WRITE, MAP_SHARED, shm_fd, 0);
            ptrread = mmap(0, 4096, PROT_READ, MAP_SHARED, shm_fd, 0);;
            sscanf(argv[1], "%d", &n);
            pid = fork();
            if(pid == 0){
                sprintf(string_number, "%d\n", n);
                sprintf(ptrwrite, "%s", string_number);
                ptrwrite += strlen(string_number);
                while(n != 1){
                    if(n % 2 == 0)
                        n = n/2;
                    else
                        n = 3 * n + 1;
                    sprintf(string_number, "%d\n", n);
                    sprintf(ptrwrite, "%s", string_number);
                    ptrwrite += strlen(string_number);
                }
            }
            else{
                wait(NULL);
                printf("%s", (char *)ptrread);
            }
            shm_unlink("Collatz");
        }
    }
    return 0;
}
