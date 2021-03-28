#include "../inc/trees.h"
#include "../inc/struct.h"
#include "../inc/defines.h"

node_t *create_node(const char *const value){
	node_t *node = (node_t *)malloc(sizeof(node_t));
	if (!node)
		return NULL;

	node->height = 1;
	node->left = (node->right = NULL);
	node->value = (char *) malloc((strlen(value) + 1) * sizeof(char));
	if (!node->value){
		free(node);
		return NULL;
	}
	strcpy(node->value, value);
	return node;
}

void free_node(node_t *node){
	free(node->value);
	free(node);
}

static unsigned int height(node_t *p){
	return p? p->height : 0;
}

static int balance_factor(node_t *p){
	return height(p->right) - height(p->left);
}

void fix_height(node_t *p){
	unsigned int hl = height(p->left);
	unsigned int hr = height(p->right);
	p->height = (hl > hr? hl : hr) + 1;
}

static node_t *rotate_right(node_t *p){
	node_t *q = p->left;
	p->left = q->right;
	q->right = p;
	fix_height(p);
	fix_height(q);
	return q;
}

static node_t *rotate_left(node_t *q){
	node_t *p = q->right;
	q->right = p->left;
	p->left = q;
	fix_height(q);
	fix_height(p);
	return p;
}

static node_t *balance(node_t *p){
	fix_height(p);

	if (balance_factor(p) == 2){
		if (balance_factor(p->right) < 0)
			p->right = rotate_right(p->right);
		return rotate_left(p);
	}

	else if (balance_factor(p) == -2){
		if (balance_factor(p->left) > 0)
			p->left = rotate_left(p->left);
		return rotate_right(p);
	}

	return p;
}

node_t *insert(node_t *p, const char *const value) 
{
	if (!p)
		return create_node(value);

	if (strcmp(p->value, value) > 0)
		p->left = insert(p->left, value);

	else if (strcmp(p->value, value) < 0)
		p->right = insert(p->right, value);

	return balance(p);
}

node_t *find_min(node_t *p) {
	return p->left? find_min(p->left) : p;
}

node_t *remove_min(node_t *p) {
	if (!p->left)
		return p->right;
	p->left = remove_min(p->left);
	return balance(p);
}

node_t *remove_a(node_t *p, const char *const value, stat_t *const stat) {
	if (!p)
		return NULL;

	if (strcmp(p->value, value) > 0){
		++stat->comp_num;
		p->left = remove_a(p->left, value, stat);
	}

	else if (strcmp(p->value, value) < 0){
		++stat->comp_num;
		p->right = remove_a(p->right, value, stat);
	}

	else {
		node_t *q = p->left;
		node_t *r = p->right;
		free_node(p);
		if (!r)
			return q;
		node_t *min = find_min(r);
		min->right = remove_min(r);
		min->left = q;
		return balance(min);
	}
	return balance(p);
}

void free_atree(node_t *vertex){
	if (!vertex)
		return;
	free_atree(vertex->left);
	free_atree(vertex->right);
	free(vertex->value);
	free(vertex);
}