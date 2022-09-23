#ifndef __MAIN_H
#define __MAIN_H

#include "bitmap.h"
#include "debug.h"
#include "hash.h"
#include "hex_dump.h"
#include "limits.h"
#include "list.h"
#include "round.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct bitmap_node {
	struct bitmap *bitmap;
	char name[10];
	bool is_full;
};
struct bitmap_node bitmap_array[10];

struct list_node {
	struct list *list;
	char name[10];
	bool is_full;
};
struct list_node list_array[10];


void create_func(int *status);
void dumpdata_func(int *status);
void delete_func(int *status);

void bitmap_func(char *text);
struct bitmap_node *find_bitmap_with_name(char * name);
void bitmap_mark_func(void);
void bitmap_all_func(void);
void bitmap_any_func(void);
void bitmap_contains_func(void);
void bitmap_count_func(void);
void bitmap_dump_func(void);
void bitmap_expand_func(void);
void bitmap_set_all_func(void);
void bitmap_flip_func(void);
void bitmap_none_func(void);
void bitmap_reset_func(void);
void bitmap_scan_and_flip_func(void);
void bitmap_scan_func(void);
void bitmap_set_multiple_func(void);
void bitmap_set_func(void);
void bitmap_size_func(void);
void bitmap_test_func(void);

void hash_func(char *text);

void list_func(char *text);
struct list_node *find_list_with_name(char * name);
void list_push_front_func(void);
void list_push_back_func(void);
void list_front_func(void);
void list_back_func(void);
void list_pop_front_func(void);
void list_pop_back_func(void);
void list_insert_func(void);
void list_insert_ordered_func(void);
void list_empty_func(void);
void list_size_func(void);
void list_max_func(void);
void list_min_func(void);
void list_remove_func(void);
void list_reverse_func(void);
void list_shuffle_func(void);

#endif