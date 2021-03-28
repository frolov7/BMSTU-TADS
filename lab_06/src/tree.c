#include "../inc/trees.h"
#include "../inc/defines.h"

node_t *insert_b(node_t *vertex, const char *const value)
{
	if (!vertex){
		vertex = create_node(value);
		return vertex;
	}

	if (strcmp(vertex->value, value) > 0){
		vertex->left = insert_b(vertex->left, value);
		fix_height(vertex);
		return vertex;
	}

	if (strcmp(vertex->value, value) < 0){
		vertex->right = insert_b(vertex->right, value);
		fix_height(vertex);
		return vertex;
	}

	return vertex;
}

node_t *remove_b(node_t *vertex, const char *const value, stat_t *const stat){
	if (!vertex)
		return NULL;

	stat->comp_num++;

	if (strcmp(vertex->value, value) > 0)
		vertex->left = remove_b(vertex->left, value, stat);

	else if (strcmp(vertex->value, value) < 0)
		vertex->right = remove_b(vertex->right, value, stat);

	else {
		node_t *q = vertex->left;
		node_t *r = vertex->right;
		free_node(vertex);
		if (!r)
			return q;
		node_t *min = find_min(r);
		min->right = remove_min(r);
		min->left = q;
		return min;
	}
	return vertex;
}

void free_tree(node_t *vertex){
	if (!vertex)
		return;
	free_tree(vertex->left);
	free_tree(vertex->right);
	free(vertex->value);
	free(vertex);
}