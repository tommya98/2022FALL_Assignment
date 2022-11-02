#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void argo1_insertion_sort(void);
void argo2_quick_sort(void);
void argo3_merge_sort(void);
void argo4_my_sort(void);

int n;
int *arr;
clock_t start, end;
double running_time;

int main(int argc, char* argv[]) {
  FILE *fp;
  fp = fopen(argv[1], "r");

  fscanf(fp, "%d", &n);
  arr = (int*)malloc(sizeof(int) * n);
  for(int i = 0; i < n; i++) {
    fscanf(fp, "%d", &arr[i]);
  }

  fclose(fp);

  if(argv[2][0] == '1') {
    start = clock();
    argo1_insertion_sort();
    end = clock();
  }
  else if(argv[2][0] == '2') {
    start = clock();
    argo2_quick_sort();
    end = clock();
  }
  else if(argv[2][0] == '3') {
    start = clock();
    argo3_merge_sort();
    end = clock();    
  }
  else if(argv[2][0] == '4') {
    start = clock();
    argo4_my_sort();
    end = clock();    
  }

  running_time = (double)(end - start) / CLOCKS_PER_SEC;

  int file_name_len = strlen(argv[1]);
  char result_file_name[file_name_len + 10];
  sprintf(result_file_name, "result_%d_%s", argv[2][0] - '0', argv[1]);

  fp = fopen(result_file_name, "w");

  fprintf(fp, "%s\n", argv[1]);
  fprintf(fp, "%d\n", argv[2][0] - '0');
  fprintf(fp, "%d\n", n);
  fprintf(fp, "%f\n", running_time);
  for(int i = 0; i < n; i++) {
    fprintf(fp, "%d ", arr[i]);
  }

  fclose(fp);

  return 0;
}

void argo1_insertion_sort(void) {
  int j;
  for(int i = 1; i < n; i++) {
    int temp = arr[i];
    for(j = i - 1; j >= 0 && arr[j] > temp; j--) {
      arr[j + 1] = arr[j];
    }
    arr[j + 1] = temp;
  }
}

void argo2_quick_sort(void) {


  return;
}

void argo3_merge_sort(void) {


  return;
}

void argo4_my_sort(void) {


  return;
}