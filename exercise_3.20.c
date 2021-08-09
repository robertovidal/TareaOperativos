#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MIN_PID 300
#define MAX_PID 5000

int *bitmap;
int used = 0;
int tot = MAX_PID - MIN_PID + 1;

int allocate_map(){
  bitmap = malloc((tot) * sizeof(int));
  if(bitmap){
    return 1;
  }
  return -1;
}

int allocate_pid(){
  if(used == tot){
    return -1;
  }

  int pid;
  if(bitmap[used] == 0){
    bitmap[used] = 1;
    pid = MIN_PID + used;
  } else {
    for(int i = 0; i < tot; i++){
      if(bitmap[i] == 0){
        bitmap[i] = 1;
        pid = MIN_PID + i;
        break;
      }
    }
  }
  used++;
  return pid;
}

void release_pid(int pid){
  if(pid < MIN_PID || pid > MAX_PID){
    printf("Invalid pid");
    return;
  }
  used--;
  bitmap[pid-300] = 0;
}

int main(){
  int pid;
  if(allocate_map()){
    for(int i = 0; i < 15; i++){
      pid = allocate_pid();
      if(pid > 0){
        printf("pid: %d \n", pid);
      } else {
        printf("Could not allocate pid\n");
      }
    }
    free(bitmap);
  } else {
    printf("Could not allocate map");
  }
  return 0;
}