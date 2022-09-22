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

struct bitmap_item {
	struct bitmap *bitmap;
	char name[10];
	bool is_full;
};
struct bitmap_item bitmap_array[10];

void create_func(int *status);
void dumpdata_func(int *status);
void delete_func(int *status);

void bitmap_func(char *text);
void bitmap_mark_func(void);
void bitmap_all_func(void);
void bitmap_any_func(void);
void bitmap_contains_func(void);
void bitmap_count_func(void);

void hash_func(char *text);


void list_func(char *text);


#endif