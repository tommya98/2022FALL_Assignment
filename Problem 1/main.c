#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


int Maximum_Sum_Subrectangle_1(int **arr); //O(n^6) algorithm
int Maximum_Sum_Subrectangle_2(int **arr); //O(n^4) algorithm
int Maximum_Sum_Subrectangle_3(int **arr); //O(n^3) algorithm


int row, column, sum;
clock_t start, end;
double running_time;


int main(int argc, char* argv[]) {
  // 입력 파일 읽기
  FILE *fp;
  fp = fopen(argv[1], "r");

  fscanf(fp, "%d", &row);
  fscanf(fp, "%d", &column);

  int **arr = (int**)malloc(sizeof(int*) * row);
  for(int i = 0; i < row; i++) {
    arr[i] = (int*)malloc(sizeof(int) * column);
  }

  for(int i = 0; i < row; i++) {
    for(int j = 0; j < column; j++) {
      fscanf(fp, "%d", &arr[i][j]);
    }
  }

  fclose(fp);


  // 알고리즘 수행
  start = clock();

  if(argv[2][0] == '1') {
    sum = Maximum_Sum_Subrectangle_1(arr);
  }
  else if(argv[2][0] == '2') {
    sum = Maximum_Sum_Subrectangle_2(arr);
  }
  else if(argv[2][0] == '3') {
    sum = Maximum_Sum_Subrectangle_3(arr);
  }

  end = clock();
  running_time = (double)(end - start) / CLOCKS_PER_SEC * 1000;


  // 출력 파일 작성
  int file_name_len = strlen(argv[1]);
  char result_file_name[file_name_len + 8];
  sprintf(result_file_name, "result_%s", argv[1]);

  fp = fopen(result_file_name, "w");

  fprintf(fp, "%s\n", argv[1]);
  fprintf(fp, "%d\n", argv[2][0] - '0');
  fprintf(fp, "%d\n", row);
  fprintf(fp, "%d\n", column);
  fprintf(fp, "%d\n", sum);
  fprintf(fp, "%g", running_time);

  fclose(fp);


  return 0;
}


int Maximum_Sum_Subrectangle_1(int **arr) {
  int max = arr[0][0];

  for(int left_top = 0; left_top < row; left_top++) {
    for(int left_bottom = left_top; left_bottom < row; left_bottom++) {
      for(int right_top = 0; right_top < column; right_top++) {
        for(int right_bottom = right_top; right_bottom < column; right_bottom++) {
          int sum = 0;
          for(int i = left_top; i <= left_bottom; i++) {
            for(int j = right_top; j <= right_bottom; j++) {
              sum += arr[i][j];
            }
          }
          if(sum > max) {
            max = sum;
          }
        }
      }
    }
  }

  return max;
}

int Maximum_Sum_Subrectangle_2(int **arr) {
  
  return 20000;
}

int Maximum_Sum_Subrectangle_3(int **arr) {

  return 30000;
}