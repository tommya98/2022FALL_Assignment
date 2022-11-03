// make random number input file
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 10

int main(void) {
  int arr[SIZE];

  srand(time(NULL));

  for(int i = 0; i < SIZE; i++) {
    arr[i] = (( rand() % 33 ) * ( rand() % 33 ) * ( rand() % 33) * ( rand() * 33) * (rand() % 33 )) + 1;
    if(arr[i] == 1 || arr[i] == -1) {
      i--;
    }
    if(arr[i] < 0) {
      arr[i] = -arr[i];
    }
  }  

  FILE *fp;
  fp = fopen("input00001.txt", "w");

  fprintf(fp, "%d ", SIZE);
  for(int i = 0; i < SIZE; i++) {
    fprintf(fp, "%d ", arr[i]);
  }

  fclose(fp);

  return 0;
}