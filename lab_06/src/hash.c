#include "../inc/hash.h"
#include "../inc/defines.h"

int next(const int num){
	int flag;
	int max, current = num + 1 + num % 2;
	while (1){
		flag = 1;
		max = sqrt(current) + 1;
		for (int i = 2; i <= max; i++)
			if (!(current % i)){
				flag = 0;
				break;
			}
		if (flag)
			return current;
		current += 2;
	}
}

hash_t *init_table(const int base){
	hash_t *table = (hash_t *) malloc(sizeof(hash_t));
	if (!table)
		return NULL;

	table->data = (node_h **) calloc(base, sizeof(node_h *));
	if (!table->data)
		return NULL;

	table->base = base;
	return table;
}

void destruct(hash_t *table){
	node_h *temp;
	for (int i = 0; i < table->base; i++)
		while (table->data[i]){
			temp = table->data[i]->next;
			free(table->data[i]->data);
			table->data[i]->data = NULL;
			free(table->data[i]);
			table->data[i] = temp;
		}
	free(table->data);
	free(table);
}

int rebase(hash_t **table, const int new_base){
	hash_t *new_table = init_table(new_base);
	if (!new_table)
		return 4;

	node_h *el;
	for (int i = 0; i < (*table)->base; i++){
		el = (*table)->data[i];
		while (el){
			if (add(new_table, el->data)){
				destruct(new_table);
				return 5;
			}
			el = el->next;
		}
	}
	destruct(*table);
	*table = new_table;
	return SUCCESS;
}

int hash_func(const char *const key, const int base){
	if (!key)
		return -1;
	int sum = 0, j = -1;
	while (key[++j])
		sum += key[j];
	return sum % base;
}

node_h *create_node_h(const char *const key){
	node_h *temp = (node_h *) calloc(1, sizeof(node_h));
	if (!temp)
		return NULL;
	temp->data = (char *)malloc((strlen(key) + 1) * sizeof(char));
	if (!temp->data){
		free(temp);
		return NULL;
	}
	strcpy(temp->data, key);
	return temp;
}

int add(hash_t *const table, const char *const key){
	if (!key || !table)
		return 1;

	int pos = hash_func(key, table->base);

	if (!table->data[pos]){
		node_h *temp = create_node_h(key);
		if (!temp)
			return 4;
		table->data[pos] = temp;
		return SUCCESS;
	}

	node_h *el = table->data[pos];
	for (int i = 0; i < COLLISION_MAX - 1; i++){

		if (!strcmp(el->data, key))
			return 17;

		if (!el->next){
			node_h *temp = create_node_h(key);
			if (!temp)
				return 4;
			el->next = temp;
			return SUCCESS;
		}

		el = el->next;
	}
	return 1;
}

int get(hash_t *const table, const char *const key)
{
	if (!key || !table)
		return -2;

	int pos = hash_func(key, table->base);
	node_h *el = table->data[pos];
	while (el){
		if (!strcmp(el->data, key))
			return SUCCESS;
		el = el->next;
	}
	return -2;
}

int remove_h(hash_t *const table, const char *const key, stat_t *const stat){
	if (!key || !table)
		return 2;

	int pos = hash_func(key, table->base);
	node_h *el = table->data[pos];
	if (!el)
		return 2;

	++stat->comp_num;
	if (!strcmp(el->data, key)){
		el = el->next;
		free(table->data[pos]->data);
		free(table->data[pos]);
		table->data[pos] = el;
		return SUCCESS;
	}
	while (el->next){
		++stat->comp_num;
		if (!strcmp(el->next->data, key)){
			node_h *temp = el->next->next;
			free(el->next->data);
			free(el->next);
			el->next = temp;
			return SUCCESS;
		}
		el = el->next;
	}
	return 2;
}