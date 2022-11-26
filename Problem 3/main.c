#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct node {
  char c;
  int freq;
  struct node* left;
  struct node* right;
};

FILE *fp, *fp2;
int n, bits, size;
int char_freq[128];
long long code[128];
char code_char[128][128];
char c, word;
struct node* tree[128];

void init(void);
struct node* make_node(char c, int freq, struct node* left, struct node* right);
struct node* make_huffman_tree(void);
void make_code(struct node* root, long long a);
void modify_code(void);
void print_metadata(FILE* fp);
void put_bit(unsigned a, FILE *fp, int mode);
void read_meatdata(FILE* fp);
void decoding(struct node* root, FILE* fp, FILE* fp2);

void print_tree(struct node* node);
void print_code(void);

int main(int argc, char* argv[]) {
  struct node* root;

  if(argc != 3) {
    printf("Error!\n");
    return 0;
  }

  init();

  if(strcmp(argv[1], "-c") == 0) {
    fp = fopen(argv[2], "r");
    if(fp == NULL) {
      printf("Error!\n");
      return 0;
    }
    while(fscanf(fp, "%c", &c) != EOF) {
      char_freq[c]++;
    }
    fclose(fp);

    root = make_huffman_tree();
    make_code(root, 1);
    modify_code();

    // print_tree(root);
    // printf("=============================================");
    // print_code();

    int file_name_len = strlen(argv[2]);
    char result_file_name[file_name_len + 3];
    sprintf(result_file_name, "%s.zz", argv[2]);
    fp = fopen(argv[2], "r");
    fp2 = fopen(result_file_name, "w");

    print_metadata(fp2);

    while(fscanf(fp, "%c", &c) != EOF) {
      for(int i = 0; i < strlen(code_char[c]); i++) {
        put_bit(code_char[c][i] - '0', fp2, 0);
      }
    }
    put_bit(0, fp2, 1);
                
    fclose(fp);
    fclose(fp2);
  }

  else if(strcmp(argv[1], "-d") == 0) {
    int file_name_len = strlen(argv[2]);
    char result_file_name[file_name_len + 3];
    sprintf(result_file_name, "%s.yy", argv[2]);
    fp = fopen(argv[2], "r");
    if(fp == NULL) {
      printf("Error!\n");
      return 0;
    }
    fp2 = fopen(result_file_name, "w");

    read_meatdata(fp);

    root = make_huffman_tree();
    make_code(root, 1);
    modify_code();

    // print_tree(root);
    // printf("=============================================");
    // print_code();

    decoding(root, fp, fp2);

    fclose(fp);
    fclose(fp2);
  }

  else {
    printf("Error!\n");
    return 0;
  }

  return 0;
}

void init(void) {
  n = 0;
  bits = 7;
  size = 0;
  c = 0;
  word = 0;
  for(int i = 0; i < 128; i++) {
    char_freq[i] = 0;
    code[i] = -1;
    tree[i] = NULL;
  }
}

struct node* make_node(char c, int freq, struct node* left, struct node* right) {
  struct node* temp = (struct node*)malloc(sizeof(struct node));
  temp->c = c;
  temp->freq = freq;
  temp->left = left;
  temp->right = right;

  return temp;
}

struct node* make_huffman_tree(void) {
	int t, min, min2;
	int check[128] = {0};

  for(int i = 0; i < 128; i++) {
    if(char_freq[i] != 0) {
      tree[n++] = make_node(i, char_freq[i], NULL, NULL);
    }
  }

  for(int i = 0; i < n - 1; i++) {
    t = 0;
    while(check[t] == -1) {
      t++;
    }
    for(min = t; t < n - 1; t++) {
      if(check[t] != -1 && tree[min]->freq > tree[t]->freq) {
        min = t;
      }
    }

    t = 0;
    while(check[t] == -1 || t == min) {
      t++;
    }
    for(min2 = t; t < n; t++) {
      if(check[t] != -1 && t != min && tree[min2]->freq > tree[t]->freq) {
        min2 = t;
      }
    }

    tree[min] = make_node(0, tree[min]->freq + tree[min2]->freq, tree[min], tree[min2]);
    check[min2] = -1;
  }

  return tree[min];
}

void make_code(struct node* root, long long a) {
  if(root->left == NULL && root->right == NULL) {
    code[root->c] = a;
  }
  else {
    if(root->left != NULL) {
      make_code(root->left, a * 10);
    }
    if(root->right != NULL) {
      make_code(root->right, a * 10 + 1);
    }
  }
}

void modify_code(void) {
  for(int i = 0; i < 128; i++) {
    if(code[i] == -1) {
      continue;
    }

    sprintf(code_char[i], "%lld", code[i]);
    for(int j = 0; j < strlen(code_char[i]); j++) {
      code_char[i][j] = code_char[i][j + 1];
    }
  }
}

void print_metadata(FILE* fp) {
  for(int i = 0; i < 128; i++) {
    if(char_freq[i] != 0) {
      fprintf(fp, "%c%d ", i, char_freq[i]);
    }
  }
  fprintf(fp, "%c%d", 'a', 0);
}

void put_bit(unsigned a, FILE *fp, int mode) {
  if(bits < 0 || mode == 1) {
    fprintf(fp, "%c", word);
    word = 0;
    bits = 7;
  }

  word |= (a << (bits--));
}

void read_meatdata(FILE* fp) {
  int t;
  while(1) {
    fscanf(fp, "%c%d", &c, &t);
    if(t == 0) {
      break;
    }
    char_freq[c] = t;
    fscanf(fp, "%c", &c);
  }
}

void decoding(struct node* root, FILE* fp, FILE* fp2) {
  int a;
  struct node* temp = root;
  size = 0;

  while(fscanf(fp, "%c", &c)) {
    for(int i = 0; i < 8; i++) {
      a = (c & (0x80 >> i)) >> (7 - i);
      if(a == 1) {
        temp = temp->right;
      }
      else if(a == 0) {
        temp = temp->left;
      }
      if(temp->right == NULL && temp->left == NULL) {
        fprintf(fp2, "%c", temp->c);
        temp = root;
        size++;
      }
      if(size == root->freq) {
        return;
      }
    }
  }
}

void print_tree(struct node* node) {
  if(node == NULL) {
    return;
  }

  printf("%c freq: %d ", node->c, node->freq);
  if(node->left != NULL) {
    printf("left: %c, right: %c\n", node->left->c, node->right->c);
  }
  printf("\n");
  print_tree(node->left);
  print_tree(node->right);
}

void print_code(void) {
  for(int i = 0; i < 128; i++) {
    if(code[i] != -1) {
      printf("%c: %s\n", i, code_char[i]);
    }
  }
}