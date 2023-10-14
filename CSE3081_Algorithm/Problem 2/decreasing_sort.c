// make random number reverse input file
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void merge_sort(int left, int right);
void merge(int left, int middle, int right);

int n;
int *arr;

int main(int argc, char* argv[]) {
  FILE *fp;
  fp = fopen(argv[1], "r");
  fscanf(fp, "%d", &n);
  arr = (int*)malloc(sizeof(int) * n);
  for(int i = 0; i < n; i++) {
    fscanf(fp, "%d", &arr[i]);
  }
  fclose(fp);

  merge_sort(0, n - 1); 

  fp = fopen("input00011.txt", "w");
  fprintf(fp, "%d ", n);
  for(int i = n - 1; i >= 0; i--) {
    fprintf(fp, "%d ", arr[i]);
  }
  fclose(fp);

  return 0;
}

void merge_sort(int left, int right) {
  if(left < right) {
    int middle = (left + right) / 2;
    merge_sort(left, middle);
    merge_sort(middle + 1, right);
    merge(left, middle, right);
  }
}

void merge(int left, int middle, int right) {
  int n_left = middle - left + 1, n_right = right - middle, i = 0, j = 0, k = left;

  int *temp_left = (int*)malloc(sizeof(int) * n_left);
  for(int t = 0; t < n_left; t++) {
    temp_left[t] = arr[left + t];
  }
  int *temp_right = (int*)malloc(sizeof(int) * n_right);
  for(int t = 0; t < n_right; t++) {
    temp_right[t] = arr[middle + t + 1];
  }

  while(i < n_left && j < n_right) {
    if(temp_left[i] <= temp_right[j]) {
      arr[k++] = temp_left[i++];
    }
    else {
      arr[k++] = temp_right[j++];
    }
  }

  while(i < n_left) {
    arr[k++] = temp_left[i++];
  }
  while(j < n_right) {
    arr[k++] = temp_right[j++];
  }
}