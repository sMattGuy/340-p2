#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int main(){
  time_t t;
  int n = 10000;
  int randnums[n];
  srand((unsigned)time(&t));
  for(int i=0;i<n;++i){
    randnums[i] = rand();
  }
  for(int i=0;i<n;++i)
    printf("%d ",randnums[i]);
  return 0;
}
