#include "main.h"

int main(void) {
  char text[50]; // stdin 저장
  int status = 0; // 1: bitmap, 2: hash, 3: list

  while(1) {
    scanf("%s", text);

    if(strcmp("quit", text) == 0) {
      break;
    }
    else if(strcmp("create", text) == 0) {
      create_func(&status);
    }
    else if(strcmp("dumpdata", text) == 0) {
      dumpdata_func(&status);
    }
    else if(strcmp("delete", text) == 0) {
      delete_func(&status);
    }
    else if(status == 1) {
      bitmap_func(text);
    }
    else if(status == 2) {
      hash_func(text);
    }
    else if(status == 3) {
      list_func(text);
    }
  }

  return 0;
}


void create_func(int *status) {
  char text[50];

  scanf("%s", text);

  if(strcmp("bitmap", text) == 0) { // create bitmap
    *status = 1;

    char new_bitmap_name[10];
    int new_bitmap_size;
    scanf("%s", new_bitmap_name);
    scanf("%d", &new_bitmap_size);

    struct bitmap_item *temp = bitmap_array;
    while(temp->is_full == true) {
      temp++;
    }
    strcpy(temp->name, new_bitmap_name);
    temp->bitmap = bitmap_create(new_bitmap_size);
    temp->is_full = true;
  }
  else if(strcmp("hash", text) == 0) { // create hash
    *status = 2;
    
  }
  else if(strcmp("list", text) == 0) { // create list
    *status = 3;
    
  }
}


void dumpdata_func(int *status) {
  char name[50];

  scanf("%s", name);

  if(*status == 1) { // dumpdata bitmap
    struct bitmap_item *temp = bitmap_array;
    while(1) {
      if(strcmp(temp->name, name) == 0) {
        break;
      }
      temp++;
    }

    for(int i = 0; i < bitmap_size(temp->bitmap); i++) {
      if(bitmap_test(temp->bitmap, i) == true) {
        printf("1");
      }
      else {
        printf("0");
      }
    }
    printf("\n");
  }
  else if(*status == 2) { //dumpdata hash

  }
  else if(*status == 3) { //dumpdata list

  }
}


void delete_func(int *status) {
  char name[10];
  
  if(*status == 1) { //delete beatmap
    scanf("%s", name);

    struct bitmap_item *temp = bitmap_array;
    while(1) {
      if(strcmp(temp->name, name) == 0) {
        break;
      }
      temp++;
    }
    bitmap_destroy(temp->bitmap);
    temp->bitmap = NULL;
    strcpy(temp->name, "\0");
    temp->is_full = false;
  }
  else if(*status == 2) {

  }
  else if(*status == 3) {

  }
}


void bitmap_func(char *text) {
  if(strcmp("bitmap_mark", text) == 0) {
    bitmap_mark_func();
  }
  else if(strcmp("bitmap_all", text) == 0) {
    bitmap_all_func();
  }
  else if(strcmp("bitmap_any", text) == 0) {
    bitmap_any_func();
  }
  else if(strcmp("bitmap_contains", text) == 0) {
    bitmap_contains_func();
  }
  else if(strcmp("bitmap_count", text) == 0) {
    bitmap_count_func();
  }
  else if(strcmp("bitmap_dump", text) == 0) {
    bitmap_dump_func();
  }
  else if(strcmp("bitmap_expand", text) == 0) {
    bitmap_expand_func();
  }
  else if(strcmp("bitmap_set_all", text) == 0) {
    bitmap_set_all_func();
  }
  else if(strcmp("bitmap_flip", text) == 0) {
    bitmap_flip_func();
  }
  else if(strcmp("bitmap_none", text) == 0) {
    bitmap_none_func();
  }
  else if(strcmp("bitmap_reset", text) == 0) {
    bitmap_reset_func();
  }
  else if(strcmp("bitmap_scan_and_flip", text) == 0) {
    bitmap_scan_and_flip_func();
  }
}

void bitmap_mark_func(void) {
  char name[10];
  scanf("%s", name);

  struct bitmap_item *temp = bitmap_array;
  while(1) {
    if(strcmp(temp->name, name) == 0) {
      break;
    }
    temp++;
  }

  int a;
  scanf("%d", &a);
  bitmap_set_multiple(temp->bitmap, a, 1, true);
}

void bitmap_all_func(void) {
  char name[10];
  scanf("%s", name);

  struct bitmap_item *temp = bitmap_array;
  while(1) {
    if(strcmp(temp->name, name) == 0) {
      break;
    }
    temp++;
  }

  int a, b;
  scanf("%d %d", &a, &b);
  if(bitmap_all(temp->bitmap, a, b) == true) {
    printf("true\n");
  }
  else {
    printf("false\n");
  }
}

void bitmap_any_func(void) {
  char name[10];
  scanf("%s", name);

  struct bitmap_item *temp = bitmap_array;
  while(1) {
    if(strcmp(temp->name, name) == 0) {
      break;
    }
    temp++;
  }

  int a, b;
  scanf("%d %d", &a, &b);
  if(bitmap_any(temp->bitmap, a, b) == true) {
    printf("true\n");
  }
  else {
    printf("false\n");
  }
}

void bitmap_contains_func(void) {
  char name[10];
  scanf("%s", name);

  struct bitmap_item *temp = bitmap_array;
  while(1) {
    if(strcmp(temp->name, name) == 0) {
      break;
    }
    temp++;
  }

  int a, b;
  char c[6];
  bool d = false;
  scanf("%d %d %s", &a, &b, c);
  if(strcmp(c, "true") == 0) {
    d = true;
  }
  if(bitmap_contains(temp->bitmap, a, b, d) == true) {
    printf("true\n");
  }
  else {
    printf("false\n");
  }
}

void bitmap_count_func(void) {
  char name[10];
  scanf("%s", name);

  struct bitmap_item *temp = bitmap_array;
  while(1) {
    if(strcmp(temp->name, name) == 0) {
      break;
    }
    temp++;
  }

  int a, b;
  char c[6];
  bool d = false;
  scanf("%d %d %s", &a, &b, c);
  if(strcmp(c, "true") == 0) {
    d = true;
  }
  printf("%ld\n", bitmap_count(temp->bitmap, a, b, d));
}

void bitmap_dump_func(void) {
  char name[10];
  scanf("%s", name);

  struct bitmap_item *temp = bitmap_array;
  while(1) {
    if(strcmp(temp->name, name) == 0) {
      break;
    }
    temp++;
  }

  bitmap_dump(temp->bitmap);
}

void bitmap_expand_func(void) {
  char name[10];
  scanf("%s", name);

  struct bitmap_item *temp = bitmap_array;
  while(1) {
    if(strcmp(temp->name, name) == 0) {
      break;
    }
    temp++;
  }

  int a;
  scanf("%d", &a);
  temp->bitmap = bitmap_expand(temp->bitmap, bitmap_size(temp->bitmap) + a);
}

void bitmap_set_all_func(void) {
  char name[10];
  scanf("%s", name);

  struct bitmap_item *temp = bitmap_array;
  while(1) {
    if(strcmp(temp->name, name) == 0) {
      break;
    }
    temp++;
  }

  char a[10];
  scanf("%s", a);
  if(strcmp(a, "true") == 0) {
    bitmap_set_all(temp->bitmap, true);
  }
  else {
    bitmap_set_all(temp->bitmap, false);
  }
}

void bitmap_flip_func(void) {
  char name[10];
  scanf("%s", name);

  struct bitmap_item *temp = bitmap_array;
  while(1) {
    if(strcmp(temp->name, name) == 0) {
      break;
    }
    temp++;
  }

  int a;
  scanf("%d", &a);
  bitmap_flip(temp->bitmap, a);
}

void bitmap_none_func(void) {
  char name[10];
  scanf("%s", name);

  struct bitmap_item *temp = bitmap_array;
  while(1) {
    if(strcmp(temp->name, name) == 0) {
      break;
    }
    temp++;
  }

  int a, b;
  scanf("%d %d", &a, &b);
  if(bitmap_none(temp->bitmap, a, b)) {
    printf("true\n");
  }
  else {
    printf("false\n");
  }
}

void bitmap_reset_func(void) {
  char name[10];
  scanf("%s", name);

  struct bitmap_item *temp = bitmap_array;
  while(1) {
    if(strcmp(temp->name, name) == 0) {
      break;
    }
    temp++;
  }

  int a;
  scanf("%d", &a);
  bitmap_reset(temp->bitmap, a);
}

void bitmap_scan_and_flip_func(void) {
  char name[10];
  scanf("%s", name);

  struct bitmap_item *temp = bitmap_array;
  while(1) {
    if(strcmp(temp->name, name) == 0) {
      break;
    }
    temp++;
  }

  int a, b;
  char c[10];
  scanf("%d %d %s", &a, &b, c);
  if(strcmp(c, "true") == 0) {
    printf("%lu\n", bitmap_scan_and_flip(temp->bitmap, a, b, true));
  }
  else {
    printf("%lu\n", bitmap_scan_and_flip(temp->bitmap, a, b, false));
  }
}

void hash_func(char *text) {
  printf("hash_func\n");
}


void list_func(char *text) {
  printf("list_func\n");
}
