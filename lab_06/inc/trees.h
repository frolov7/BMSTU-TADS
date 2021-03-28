#ifndef _TREES_H_
#define _TREES_H_

#include "struct.h"
#include <stdlib.h>
#include <string.h>
typedef struct node_t {
	unsigned int height; //высота узла
	struct node_t *left; //левое поддеревье
	struct node_t *right; //правое поддеревье
	char *value; //указатель на строку с данными
} node_t;


node_t *create_node(const char *const value);
void free_node(node_t *node);
void fix_height(node_t *p);
node_t *find_min(node_t *p);
node_t *remove_min(node_t *p);
node_t *remove_a(node_t *p, const char *const value, stat_t *const stat);
void free_atree(node_t *vertex);
node_t *insert(node_t *p, const char *const value);

node_t *insert_b(node_t *vertex, const char *const value);
node_t *remove_b(node_t *vertex, const char *const value, stat_t *const stat);
void free_tree(node_t *vertex);

#endif