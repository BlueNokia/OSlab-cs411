/*
finding prime numbers between 1 and MAX using n child processes
and the parent will be waiting till all the child are finished processing
*/

#include<stdio.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdlib.h>

// function to find all prime number between a and b
void prime(int a, int b){
    int i, j, count;
    for(i=a;i<=b;i++){
        count = 0;
        for(j=1; j<=i; j++){
            if(i%j == 0){
                count++;
            }
        }
        if(count == 2){
            printf("%d\n",i);
        }
    }
}

int main(){
  int max, n, i,j;
  printf("Enter max and n: ");
  scanf("%d %d", &max, &n);

  int batch_size = max/n;

  for(i=0, j=1; i<n; i++){
    if(fork() == 0){
      prime(j,j+batch_size-1);
      exit(0);
    }
    j=j+batch_size;
  }

  // last left out calculations for parent
  prime(j,max);

  // this will make the parent process wait, till all it's childs are done
  for(i=0;i<n;i++){
    wait(NULL);
  }

  printf("-- parent waited till the end --\n");
  return 0;
}


















//
