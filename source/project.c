#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
//size of the random number array
#define SIZE 10000

//global variables
int randNum[SIZE];
int grandSum = 0;

//second thread that will be used by the first thread
void *secondBreak(void *param){
  //initial pos in rand array
  int start = (int)param;
  //sum of the array split over 20 threads in 5 seperate parents
  for(int i=start;i<start+100;i++){
    grandSum += randNum[i];
  }
  pthread_exit(NULL);
}

void *firstBreak(void *param){
  int start = (int)param;
  //initialization of the 20 threads for the parent
  pthread_t breakThreads[20];
  
  for(int i=0;i<20;i++){
    int subStart = i*100+start;
    pthread_create(&breakThreads[i], NULL, secondBreak, (void *)subStart);
  }
  for(int i=0;i<20;i++){
    pthread_join(breakThreads[i],NULL);
  }
  pthread_exit(NULL);
}

int main(int argc, char *argv[]){
  time_t t;
  srand((unsigned)time(&t));
  for(int i=0;i<SIZE;i++)
    randNum[i] = rand()%101;
  
  pthread_t threads[5];
  
  //start of thread summation
  for(int i=0;i<5;i++){
    int start = i*1999+i;
    pthread_create(&threads[i], NULL, firstBreak, (void *)start);
  }
  
  for(int i=0;i<5;i++){
    pthread_join(threads[i],NULL);
  }
  
  printf("Final Total From Threads:%d\n",grandSum);
  //end of thread summation

  //linear summation for checking purposes
  int sum = 0;
  for(int i=0;i<SIZE;i++)
    sum+=randNum[i];

  printf("Final Total From Linear Add:%d\n",sum);
  //end of linear submation
  
  return 0;
}
