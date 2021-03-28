#include "../inc/io.h"
#include "../inc/defines.h"

char buffer[BUFF_LEN] = {0};

void menu(){
	printf("\nMENU\n"
		"0. Exit\n\n"
		"1. Delete word\n"
		"2. Show binary tree\n"
		"3. Show AUS-tree\n"
		"4. Show hash-table\n"
		"5. Delete comparison\n"
		"6. Rebase\n"
		"\nInput: ");
}

int input_hash_table(hash_t **const table, FILE *const stream){
	while (fscanf(stream, "%s", buffer) == 1)
		if (add(*table, buffer) == ADD_ERROR){
			int cur_base = next((*table)->base);
			while (rebase(table, cur_base))
				cur_base = next(cur_base);
		}
	return SUCCESS;
}

int input_tree(node_t **vertex_b, FILE *const stream){
	while (fscanf(stream, "%s", buffer) == 1)
		*vertex_b = insert_b(*vertex_b, buffer);
	return SUCCESS;
}

void tree_to_atree(node_t *vertex_b, node_t **vertex){
	if (!vertex_b)
		return;
	*vertex = insert(*vertex, vertex_b->value);
	tree_to_atree(vertex_b->left, vertex);
	tree_to_atree(vertex_b->right, vertex);
}

void print_hash_table(const hash_t *const table){
	printf("\033[1;29m|  HASH  |        VALUE        |\n");
	node_h *elem;
	for (int i = 0; i < table->base; i++){
		elem = table->data[i];
		if (!elem)
			continue;
		printf("|  %4d  |   \033[1;32m%15s \033[1;37m  |\n", i, elem->data);
		elem = elem->next;
		while (elem){
			printf("|  %4d  |   \033[1;31m%15s \033[1;37m  |\n", i, elem->data);
			elem = elem->next;
		}
	}
}

void print_vertex(const node_t *const vertex, const int depth){
	for (int i = 0; i < depth; i++)
		printf("%10s", "|");
	printf("%10d: %s\n", depth, vertex->value);
}

void print_tree(const node_t *const vertex, const int depth){
	if (!vertex)
		return;
	printf("\033[1;29m");
	print_tree(vertex->right, depth + 1);
	print_vertex(vertex, depth);
	print_tree(vertex->left, depth + 1);
	printf("\033[1;29m");
}

void print_stat(const stat_t *const stat_array){
	printf("\nFor simple binary tree:\n");
	printf("Number of comparisons: %d;\nTime: %lld ticks;\n", stat_array[TREE].comp_num, stat_array[TREE].time);
	printf("\nFor AUS-tree:\n");
	printf("Number of comparisons: %d;\nTime: %lld ticks;\n", stat_array[ATREE].comp_num, stat_array[ATREE].time);
	printf("\nFor hash-table:\n");
	printf("Number of comparisons: %d;\nTime: %lld ticks;\n", stat_array[HASH_TABLE].comp_num, stat_array[HASH_TABLE].time / 2);
	printf("\nFor file:\n");
	printf("Number of comparisons: %d;\nTime: %lld ticks;\n", stat_array[FILE_LIST].comp_num, stat_array[FILE_LIST].time);
}