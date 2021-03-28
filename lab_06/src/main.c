#include "../inc/trees.h"
#include "../inc/hash.h"
#include "../inc/io.h"
#include "../inc/struct.h"
#include "../inc/defines.h"
#include <string.h>
#include <stdint.h>

uint64_t tick(void){
	uint32_t high, low;
	__asm__ __volatile__ (
		"rdtsc\n"
		"movl %%edx, %0\n"
		"movl %%eax, %1\n"
		: "=r" (high), "=r" (low)
		:: "%rax", "%rbx", "%rcx", "%rdx"
		);

	uint64_t ticks = (uint64_t) high << 32 | low;

	return ticks;
}

extern char buffer[BUFF_LEN];

static int delete_word(FILE *const stream, const int pos, const int len){
	fseek(stream, pos, SEEK_SET);
	for (int i = 0; i < len; i++)
		fputc(' ', stream);
	return SUCCESS;
}

int remove_f(FILE *const stream, const char *const key, stat_t *const stat){
	int pos = 0;
	while (fscanf(stream, "%s", buffer) == 1){
		++stat->comp_num;
		if (!strcmp(buffer, key))
			return delete_word(stream, pos, ftell(stream) - pos);
		pos = ftell(stream);
	}
	return NO_WORD_ERROR;
}

int main(){
	setbuf(stdout, NULL);

	int flag;
	int in_base = 0;
	int mistake = 1;
	stat_t stat_array[4] = {};
	uint64_t start = 0;

	hash_t *table = NULL;
	node_t *vertex_b = NULL;
	node_t *vertex = NULL;

	int size = 0;
	char c;
	FILE *f = fopen(FILENAME, "r");
	while ((c = fgetc(f)) != EOF && c != '\0')
		if (c == '\n')
			size++;

	table = init_table(next(++size));

	menu();

	f = fopen(FILENAME, "r");
	input_hash_table(&table, f);
	fseek(f, 0, SEEK_SET);
	input_tree(&vertex_b, f);
	tree_to_atree(vertex_b, &vertex);
	fclose(f);

	while (scanf("%d", &flag) != 1){
		puts("ERROR, try again:");
		char c;
		while (scanf("%c", &c) == 1 && c != '\n');
	}
	while (1){
		printf("\n");
		switch (flag){
			case 0:
				puts("EXIT");
				goto label;
			case 1:
				printf("Word to delete: ");
				if (scanf("%254s", buffer) != 1){
					printf("INPUT ERROR.\n");
					break;
				}
				stat_array[ATREE].comp_num = 0;
				start = tick();
				vertex = remove_a(vertex, buffer, &stat_array[ATREE]);
				stat_array[ATREE].time = tick() - start;

				stat_array[TREE].comp_num = 0;
				start = tick();
				vertex_b = remove_b(vertex_b, buffer, &stat_array[TREE]);
				stat_array[TREE].time = tick() - start;

				stat_array[HASH_TABLE].comp_num = 0;
				start = tick();
				mistake = remove_h(table, buffer, &stat_array[HASH_TABLE]);
				stat_array[HASH_TABLE].time = tick() - start;

				stat_array[FILE_LIST].comp_num = 0;
				f = fopen(FILENAME, "r+");
				start = tick();
				remove_f(f, buffer, &stat_array[FILE_LIST]);
				stat_array[FILE_LIST].time = tick() - start;
				fclose(f);

				if (mistake)
					printf("No such word in structures\n");
				else{
					printf("SUCCESS\n");
					size--;
				}
				break;
			case 2:
				print_tree(vertex_b, 0);
				break;
			case 3:
				print_tree(vertex, 0);
				break;
			case 4:
				print_hash_table(table);
				break;
			case 5:
				if (mistake)
					printf("Last deletion wasn't correct or there wasn't deletion still\n");
				else
					print_stat(stat_array);
				break;
			case 6:
				printf("Input new base of table: ");
				if (scanf("%d", &in_base) != 1){
					printf("READ ERROR base value\n");
					break;
				}
				if (in_base <= 0){
					printf("Error value of base\n");
					break;
				}

				int rc = rebase(&table, in_base);
				if (rc)
					printf("Can't create table with this base.\n");
				break;
		}
		menu();
		while (scanf("%d", &flag) != 1){
			puts("\n\nERROR, try again: ");
			char c;
			while (scanf("%c", &c) == 1 && c != '\n');
		}
	}
	label:
	destruct(table);
	free_atree(vertex);
	free_tree(vertex_b);
	return SUCCESS;
}