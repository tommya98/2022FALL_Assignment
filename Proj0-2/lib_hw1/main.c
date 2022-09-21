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
    struct bitmap_item *new_bitmap = (struct bitmap_item*)malloc(sizeof(struct bitmap_item));

    scanf("%s", new_bitmap_name);
    scanf("%d", &new_bitmap_size);

		strcpy(new_bitmap->name, new_bitmap_name);
		new_bitmap->bitmap = bitmap_create(new_bitmap_size);
		new_bitmap->next = NULL;

		if(bitmap_item_head == NULL) {
      bitmap_item_head = new_bitmap;
    }
		else {
			struct bitmap_item *temp = bitmap_item_head;
			while(temp->next != NULL) {
        temp = temp->next;
      }
			temp->next = new_bitmap;
		}
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
    struct bitmap_item *temp = bitmap_item_head;
    while(strcmp(temp->name, name) != 0) {
      temp = temp->next;
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

    struct bitmap_item *temp = bitmap_item_head;
    while(1) {
		  if(temp == NULL) {
        break;
      }

		  if(strcmp(temp->name, name) == 0) {
		  	bitmap_destroy(temp->bitmap);
        if(temp == bitmap_item_head) {
		  		bitmap_item_head = NULL;
		  		free(temp);
		  		break;
		  	}

		  	struct bitmap_item *temp2 = bitmap_item_head;
		  	while(temp->next != temp) {
          temp2 = temp2->next;
        }
		  	temp2->next = temp2->next->next;
		  	free(temp);
		  	break;
		  }
		  else {
        temp = temp->next;
      }
	  }
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
  else if(strcmp("bitmap_any", text)) {
    bitmap_any_func();
  }
}

void bitmap_mark_func(void) {
  char name[10];
  scanf("%s", name);

  struct bitmap_item *temp = bitmap_item_head;
  while(strcmp(temp->name, name) != 0) {
    temp = temp->next;
  }

  int a;
  scanf("%d", &a);
  bitmap_set_multiple(temp->bitmap, a, 1, true);
}

void bitmap_all_func(void) {
  char name[10];
  scanf("%s", name);

  struct bitmap_item *temp = bitmap_item_head;
  while(strcmp(temp->name, name) != 0) {
    temp = temp->next;
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
  
}


void hash_func(char *text) {
  printf("hash_func\n");
}


void list_func(char *text) {
  printf("list_func\n");
}