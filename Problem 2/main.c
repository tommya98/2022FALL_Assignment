#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void argo1_insertion_sort(int left, int right);
void argo2_quick_sort(int left, int right);
int quick_sort_partition(int left, int right);
void argo3_merge_sort(int left, int right);
void merge_sort_merge(int left, int middle, int right);
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
    argo1_insertion_sort(0, n - 1);
    end = clock();
  }
  else if(argv[2][0] == '2') {
    start = clock();
    argo2_quick_sort(0, n - 1);
    end = clock();
  }
  else if(argv[2][0] == '3') {
    start = clock();
    argo3_merge_sort(0, n - 1);
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

void argo1_insertion_sort(int left, int right) {
  int j;
  for(int i = left + 1; i <= right; i++) {
    int temp = arr[i];
    for(j = i - 1; j >= left && arr[j] > temp; j--) {
      arr[j + 1] = arr[j];
    }
    arr[j + 1] = temp;
  }
}

void argo2_quick_sort(int left, int right) {
  if(left < right) {
    int pivot = quick_sort_partition(left, right);
    argo2_quick_sort(left, pivot - 1);
    argo2_quick_sort(pivot + 1, right);
  }
}

int quick_sort_partition(int left, int right) {
  int pivot = arr[right];
  int index = left - 1;

  for(int i = left; i < right; i++) {
    if(arr[i] <= pivot) {
      index++;
      int temp = arr[i];
      arr[i] = arr[index];
      arr[index] = temp;
    }
  }

  arr[right] = arr[index + 1];
  arr[index + 1] = pivot;

  return index + 1;
}

void argo3_merge_sort(int left, int right) {
  if(left < right) {
    int middle = (left + right) / 2;
    argo3_merge_sort(left, middle);
    argo3_merge_sort(middle + 1, right);
    merge_sort_merge(left, middle, right);
  }
}

void merge_sort_merge(int left, int middle, int right) {
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

void argo4_my_sort(void) {
  int size = 32;

  for(int i = 0; i < n; i += size) {
    if(i + size - 1 < n - 1) {
      argo1_insertion_sort(i, i + size - 1);
    }
    else {
      argo1_insertion_sort(i, n- 1);
    }
  }

  for(int i = size; i < n; i *= 2) {
    for(int left = 0; left < n; left += 2 * i) {
      int mid = left + i - 1;
      int right = left + 2 * i - 1;
      if(right > n - 1) {
        right = n - 1;
      }
      if(mid < right) {
        merge_sort_merge(left, mid, right);
      }
    }
  }
}