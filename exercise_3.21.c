#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

// Jose Pablo Fernández Cubillo
// Roberto Vidal Patiño

int main(int argc, char *argv[]){
    int n;
    int pid;
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
            sscanf(argv[1], "%d", &n);
            pid = fork();
            if(pid == 0){
                printf("%d\n", n);
                while(n != 1){
                    if(n % 2 == 0)
                        n = n/2;
                    else
                        n = 3 * n + 1;
                    printf("%d\n", n);
                }
            }
            else{
                wait(NULL);
            }
        }
    }
    return 0;
}
