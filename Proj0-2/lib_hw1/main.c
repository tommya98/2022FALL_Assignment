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

    struct bitmap_node *temp = bitmap_array;
    while(temp->is_full == true) {
      temp++;
    }
    strcpy(temp->name, new_bitmap_name);
    temp->bitmap = bitmap_create(new_bitmap_size);
    temp->is_full = true;
  }
  else if(strcmp("hashtable", text) == 0) { // create hash
    *status = 2;

  }
  else if(strcmp("list", text) == 0) { // create list
    *status = 3;
    char new_list_name[10];
    scanf("%s", new_list_name);

    struct list_node *temp = list_array;
    while(temp->is_full == true) {
      temp++;
    }
    strcpy(temp->name, new_list_name);
    temp->list = (struct list*)malloc(sizeof(struct list));
    list_init(temp->list);
    temp->is_full = true;
  }
}

void dumpdata_func(int *status) {
  char name[50];

  scanf("%s", name);

  if(*status == 1) { // dumpdata bitmap
    struct bitmap_node *temp = find_bitmap_with_name(name);

    if(bitmap_size(temp->bitmap) == 0) {
      return;
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
  struct list_node *temp_item = find_list_with_name(name);

  if(list_size(temp_item->list) == 0) {
    return;
  }

  for(struct list_elem *temp_elem = list_begin(temp_item->list); temp_elem != list_end(temp_item->list); temp_elem = list_next(temp_elem)) {
    struct list_item *temp_entry = list_entry(temp_elem, struct list_item, elem);
    printf("%d ", temp_entry->data);
  }
  printf("\n");
  }
}

void delete_func(int *status) {
  char name[10];
  
  if(*status == 1) { //delete beatmap
    scanf("%s", name);
    struct bitmap_node *temp = find_bitmap_with_name(name);

    bitmap_destroy(temp->bitmap);
    temp->bitmap = NULL;
    strcpy(temp->name, "\0");
    temp->is_full = false;
  }
  else if(*status == 2) {

  }
  else if(*status == 3) {
    scanf("%s", name);
    struct list_node *temp = find_list_with_name(name);

    temp->list = NULL;
    strcpy(temp->name, "\0");
    temp->is_full = false;
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
  else if(strcmp("bitmap_scan", text) == 0) {
    bitmap_scan_func();
  }
  else if(strcmp("bitmap_set_multiple", text) == 0) {
    bitmap_set_multiple_func();
  }
  else if(strcmp("bitmap_set", text) == 0) {
    bitmap_set_func();
  }
  else if(strcmp("bitmap_size", text) == 0) {
    bitmap_size_func();
  }
  else if(strcmp("bitmap_test", text) == 0) {
    bitmap_test_func();
  }
}

struct bitmap_node *find_bitmap_with_name(char *name) {
  struct bitmap_node *temp = bitmap_array;

  while(1) {
    if(strcmp(temp->name, name) == 0) {
      break;
    }
    temp++;
  }

  return temp;
}

void bitmap_mark_func(void) {
  char name[10];
  scanf("%s", name);
  struct bitmap_node *temp = find_bitmap_with_name(name);

  int a;
  scanf("%d", &a);
  bitmap_mark(temp->bitmap, a);
}

void bitmap_all_func(void) {
  char name[10];
  scanf("%s", name);
  struct bitmap_node *temp = find_bitmap_with_name(name);

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
  struct bitmap_node *temp = find_bitmap_with_name(name);

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
  struct bitmap_node *temp = find_bitmap_with_name(name);

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
  struct bitmap_node *temp = find_bitmap_with_name(name);

  int a, b;
  char c[6];
  bool d = false;
  scanf("%d %d %s", &a, &b, c);
  if(strcmp(c, "true") == 0) {
    d = true;
  }
  printf("%zu\n", bitmap_count(temp->bitmap, a, b, d));
}

void bitmap_dump_func(void) {
  char name[10];
  scanf("%s", name);
  struct bitmap_node *temp = find_bitmap_with_name(name);

  bitmap_dump(temp->bitmap);
}

void bitmap_expand_func(void) {
  char name[10];
  scanf("%s", name);
  struct bitmap_node *temp = find_bitmap_with_name(name);

  int a;
  scanf("%d", &a);
  temp->bitmap = bitmap_expand(temp->bitmap, bitmap_size(temp->bitmap) + a);
}

void bitmap_set_all_func(void) {
  char name[10];
  scanf("%s", name);
  struct bitmap_node *temp = find_bitmap_with_name(name);

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
  struct bitmap_node *temp = find_bitmap_with_name(name);

  int a;
  scanf("%d", &a);
  bitmap_flip(temp->bitmap, a);
}

void bitmap_none_func(void) {
  char name[10];
  scanf("%s", name);
  struct bitmap_node *temp = find_bitmap_with_name(name);

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
  struct bitmap_node *temp = find_bitmap_with_name(name);

  int a;
  scanf("%d", &a);
  bitmap_reset(temp->bitmap, a);
}

void bitmap_scan_and_flip_func(void) {
  char name[10];
  scanf("%s", name);
  struct bitmap_node *temp = find_bitmap_with_name(name);

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

void bitmap_scan_func(void) {
  char name[10];
  scanf("%s", name);
  struct bitmap_node *temp = find_bitmap_with_name(name);

  int a, b;
  char c[10];
  scanf("%d %d %s", &a, &b, c);
  if(strcmp(c, "true") == 0) {
    printf("%lu\n", bitmap_scan(temp->bitmap, a, b, true));
  }
  else {
    printf("%lu\n", bitmap_scan(temp->bitmap, a, b, false));
  }  
}

void bitmap_set_multiple_func(void) {
  char name[10];
  scanf("%s", name);
  struct bitmap_node *temp = find_bitmap_with_name(name);

  int a, b;
  char c[10];
  scanf("%d %d %s", &a, &b, c);
  if(strcmp(c, "true") == 0) {
    bitmap_set_multiple(temp->bitmap, a, b, true);
  }
  else {
    bitmap_set_multiple(temp->bitmap, a, b, false);
  }  
}

void bitmap_set_func(void) {
  char name[10];
  scanf("%s", name);
  struct bitmap_node *temp = find_bitmap_with_name(name);

  int a;
  char b[10];
  scanf("%d %s", &a, b);
  if(strcmp(b, "true") == 0) {
    bitmap_set(temp->bitmap, a, true);
  }
  else {
    bitmap_set(temp->bitmap, a, false);
  }    
}

void bitmap_size_func(void) {
  char name[10];
  scanf("%s", name);
  struct bitmap_node *temp = find_bitmap_with_name(name);

  printf("%zu\n", bitmap_size(temp->bitmap));
}

void bitmap_test_func(void) {
  char name[10];
  scanf("%s", name);
  struct bitmap_node *temp = find_bitmap_with_name(name);

  int a;
  scanf("%d", &a);
  if(bitmap_test(temp->bitmap, a) == true) {
    printf("true\n");
  }
  else {
    printf("false\n");
  }
}


void hash_func(char *text) {
  printf("hash_func\n");
}


void list_func(char *text) {
  if(strcmp("list_push_front", text) == 0) {
    list_push_front_func();
  }
  else if(strcmp("list_push_back", text) == 0) {
    list_push_back_func();
  }
  else if(strcmp("list_front", text) == 0) {
    list_front_func();
  }
  else if(strcmp("list_back", text) == 0) {
    list_back_func();
  }
  else if(strcmp("list_pop_front", text) == 0) {
    list_pop_front_func();
  }
  else if(strcmp("list_pop_back", text) == 0) {
    list_pop_back_func();
  }
  else if(strcmp("list_insert", text) == 0) {
    list_insert_func();
  }
  else if(strcmp("list_insert_ordered", text) == 0) {
    list_insert_ordered_func();
  }
  else if(strcmp("list_empty", text) == 0) {
    list_empty_func();
  }
  else if(strcmp("list_size", text) == 0) {
    list_size_func();
  }
  else if(strcmp("list_max", text) == 0) {
    list_max_func();
  }
  else if(strcmp("list_min", text) == 0) {
    list_min_func();
  }
  else if(strcmp("list_remove", text) == 0) {
    list_remove_func();
  }
  else if(strcmp("list_reverse", text) == 0) {
    list_reverse_func();
  }
  else if(strcmp("list_shuffle", text) == 0) {
    list_shuffle_func();
  }
  else if(strcmp("list_sort", text) == 0) {
    list_sort_func();
  }
  else if(strcmp("list_splice", text) == 0) {
    list_splice_func();
  }
}

struct list_node *find_list_with_name(char * name) {
  struct list_node *temp = list_array;

  while(1) {
    if(strcmp(temp->name, name) == 0) {
      break;
    }
    temp++;
  }

  return temp; 
}

void list_push_front_func(void) {
  char name[10];
  scanf("%s", name);
  struct list_node *temp = find_list_with_name(name);

  int a;
  scanf("%d", &a);
  struct list_item *new_list = (struct list_item*)malloc(sizeof(struct list_item));
  new_list->data = a;
  list_push_front(temp->list, &(new_list->elem));
}

void list_push_back_func(void) {
  char name[10];
  scanf("%s", name);
  struct list_node *temp = find_list_with_name(name);

  int a;
  scanf("%d", &a);
  struct list_item *new_list = (struct list_item*)malloc(sizeof(struct list_item));
  new_list->data = a;
  list_push_back(temp->list, &(new_list->elem));
}

void list_front_func(void) {
  char name[10];
  scanf("%s", name);
  struct list_node *temp = find_list_with_name(name);

  struct list_elem *temp_elem = list_front(temp->list);
  printf("%d\n", list_entry(temp_elem, struct list_item, elem)->data);
}

void list_back_func(void) {
  char name[10];
  scanf("%s", name);
  struct list_node *temp = find_list_with_name(name);

  struct list_elem *temp_elem = list_back(temp->list);
  printf("%d\n", list_entry(temp_elem, struct list_item, elem)->data);
}

void list_pop_front_func(void) {
  char name[10];
  scanf("%s", name);
  struct list_node *temp = find_list_with_name(name);

  list_pop_front(temp->list);
}

void list_pop_back_func(void) {
  char name[10];
  scanf("%s", name);
  struct list_node *temp = find_list_with_name(name);

  list_pop_back(temp->list);
}

void list_insert_func(void) {
  char name[10];
  scanf("%s", name);
  struct list_node *temp = find_list_with_name(name);

  int a, b;
  scanf("%d %d", &a, &b);
  struct list_item *new_list = (struct list_item*)malloc(sizeof(struct list_item));
  new_list->data = b;

  struct list_elem *temp_elem = list_begin(temp->list);
  for(int i = 0; i < a; i++) {
    temp_elem = list_next(temp_elem);
  }
  list_insert(temp_elem, &(new_list->elem));
}

void list_insert_ordered_func(void) {
  char name[10];
  scanf("%s", name);
  struct list_node *temp = find_list_with_name(name);

  int a;
  scanf("%d", &a);
  struct list_item *new_list = (struct list_item*)malloc(sizeof(struct list_item));
  new_list->data = a;
  list_insert_ordered(temp->list, &new_list->elem, list_less, NULL);
}

void list_empty_func(void) {
  char name[10];
  scanf("%s", name);
  struct list_node *temp = find_list_with_name(name);

  if(list_empty(temp->list)) {
    printf("true\n");
  }
  else {
    printf("false\n");
  }
}

void list_size_func(void) {
  char name[10];
  scanf("%s", name);
  struct list_node *temp = find_list_with_name(name);

  printf("%zu\n", list_size(temp->list));
}

void list_max_func(void) {
  char name[10];
  scanf("%s", name);
  struct list_node *temp = find_list_with_name(name);

  struct list_elem * temp_elem = list_max(temp->list, list_less, NULL);

  printf("%d\n", list_entry(temp_elem, struct list_item, elem)->data);
}

void list_min_func(void){
  char name[10];
  scanf("%s", name);
  struct list_node *temp = find_list_with_name(name);

  struct list_elem * temp_elem = list_min(temp->list, list_less, NULL);

  printf("%d\n", list_entry(temp_elem, struct list_item, elem)->data);
}

void list_remove_func(void) {
  char name[10];
  scanf("%s", name);
  struct list_node *temp = find_list_with_name(name);

  int a;
  scanf("%d", &a);
  struct list_elem *temp_elem = list_begin(temp->list);
  for(int i = 0; i < a; i++) {
    temp_elem = list_next(temp_elem);
  }
  list_remove(temp_elem);
}

void list_reverse_func(void) {
  char name[10];
  scanf("%s", name);
  struct list_node *temp = find_list_with_name(name);

  list_reverse(temp->list);
}

void list_shuffle_func(void) {
  char name[10];
  scanf("%s", name);
  struct list_node *temp = find_list_with_name(name);

  list_shuffle(temp->list);
}

void list_sort_func(void) {
  char name[10];
  scanf("%s", name);
  struct list_node *temp = find_list_with_name(name);

  list_sort(temp->list, list_less, NULL);
}

void list_splice_func(void) {
  char name[10];
  scanf("%s", name);
  struct list_node *temp1 = find_list_with_name(name);
  int a, b, c;
  scanf("%d", &a);
  scanf("%s", name);
  struct list_node *temp2 = find_list_with_name(name);
  scanf("%d %d", &b, &c);

  struct list_elem *before = list_begin(temp1->list);
  for(int i = 0; i < a; i++) {
    before = list_next(before);
  }
  struct list_elem *first = list_head(temp2->list);
  for(int i = 0; i <= b; i++) {
    first = list_next(first);
  }
  struct list_elem *last = list_head(temp2->list);
  for(int i = 0; i <= c; i++) {
    last = list_next(last);
  }
  list_splice(before, first, last);
}