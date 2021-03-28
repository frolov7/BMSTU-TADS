#include "list_stack.h"

void push_l(node_t** head, char *new_data) { 
	node_t* new_node = (node_t*)malloc(sizeof(node_t));  

	new_node->data  = malloc(strlen(new_data) + 1); 
	new_node->next = (*head);

	strcpy(new_node->data, new_data);
		  
	*head = new_node; 
	printf("\n Новый адрес: %p\n", (void*)new_node);
} 


node_t* pop_front(node_t **head){
	if(*head == NULL)
		return NULL;
	node_t *buf = *head;
	printf("\n Очищенный адрес: %p\n", (void*)buf); 
	*head = (*head)->next; 
	
	free(buf->data); 
	free(buf); 
	return *head;
}

void print_stack_l(node_t *head){
	if(head != NULL){
		printf("<-|");
		while (head != NULL){
			printf(" %s|", head->data);
			head = head->next;
		}
		printf("|");
	}
	else
	printf("Стек пуст!\n");
	
}


void freeList(node_t** head){
	node_t *cur = *head;
	while(cur != NULL){
		free(cur->data);
		cur = cur->next;
	}
}


node_t* print_back_list(node_t *head){
	while (head != NULL){
		printf(" %s", head->data);
		pop_front(&head);
	}
	return head;
}


node_t* reverse(node_t* head){
	if(head->next == NULL)
		return head;
	node_t* prev = NULL;
	node_t* current = head;
	node_t* next;
	while (current != NULL){
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
	}
	head = prev;
	return head;
}


int count(node_t *head){
	int count = 0;
	while (head != NULL){
		count++;
		head = head->next;
	}
	return count;
}

void print_addresses(node_t *head){
	while (head != NULL){
		printf("%p\n", (void*)head);
		head = head->next;
	}
}

node_t** delete_from_list(node_t *head, node_t **point){
	while(head != NULL){
		if((void*)head == (void*)point[1]){
			free(point[1]);
			*point = NULL;
			break;
		}
		head = head->next;

	}
	return point;
}

void push_l_test(node_t** head, char *new_data) { 
	node_t* new_node = (node_t*)malloc(sizeof(node_t)); 

	new_node->data  = malloc(strlen(new_data) + 1); 
	new_node->next = (*head); 

	strcpy(new_node->data, new_data);
		  
	*head = new_node; 
} 

node_t* pop_test(node_t **head){
	if(*head == NULL)
		return NULL;
	node_t *buf = *head;
	*head = (*head)->next;
	
	free(buf->data);
	free(buf);
	return *head;
}

