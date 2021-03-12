#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int sum; //data shared by threads
void *runner(void *param); //threads call this function

int main(int argc, char *argv[]){
  pthread_t tid; //thread identifier
  pthread_attr_t attr; //thread attributes
  //set default thread attributes
  pthread_attr_init(&attr);
  //creates thread
  pthread_create(&tid, &attr, runner, argv[1]);
  //waits for thread to exit
  pthread_join(tid,NULL);

  printf("sum = %d\n",sum);
}

//function the threads run
void *runner(void *param){
  int i, upper = atoi(param);
  sum = 0;

  for(i = 1; i<= upper; i++)
      sum += i;
  pthread_exit(0);
}
