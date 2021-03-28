#ifndef _HASH_H_
#define _HASH_H_

#include "struct.h"
#include <string.h>
#include <stdlib.h>
#include <math.h>
typedef struct node_h
{
	char *data;
	struct node_h *next;
} node_h;

typedef struct hash_t
{
	node_h **data;
	int base;
} hash_t;

hash_t *init_table(const int base);
int next(const int number);
int rebase(hash_t **table, const int new_base);
int add(hash_t *const table, const char *const key);
int get(hash_t *const table, const char *const key);
int remove_h(hash_t *const table, const char *const key, stat_t *const stat);
void destruct(hash_t *table);

#endif