#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

// NOTA: usando el comando ps -l en mi computadora no 
// aparecía el proceso, pero usando este otro sí aparece
// ps aux | grep exercise_3.19
int main(){
  int pid = fork();
  int status;
  if(pid == 0){
    printf("pid:%d\n", getpid());
    exit(0);
  } else {
    printf("Child pid:%d, Parent pid:%d\n", pid, getpid());
  }
  sleep(10);
  return 0;
}