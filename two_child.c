#include<stdio.h>
#include<sys/wait.h>
#include<unistd.h>

int main(){
  int id_fc, id_sc;
  // first child
  int first_child_id = fork();
  if(first_child_id == 0){
    // child process
    printf("CHILD 1 @ PID: %d & PPID: %d\n", getpid(), getppid());
    printf("CHILD 1 EXECUTION COMPLETED\n\n");
  } else{
    // parent process
    id_fc = wait(NULL);
    int second_child_id = fork();
    if(second_child_id == 0){
      printf("CHILD 2 @ PID: %d & PPID: %d\n", getpid(), getppid());
      printf("CHILD 2 EXECUTION COMPLETED\n\n");
    } else{
      // parent process
      id_sc = wait(NULL);
      printf("-- parent now executes --\n");
      printf("1 CHILD PID: %d AND 2 CHILD PID: %d\n\n", id_fc, id_sc);
    }
  }
}
