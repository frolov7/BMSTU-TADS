#include "arr_stack.h"

Stack *init(){
	Stack * create_stack = malloc(sizeof(Stack));
	
	if (create_stack == NULL)
		exit(OUT_OF_MEMORY);
	
	create_stack->size = SIZE;
	create_stack->strings = malloc(create_stack->size * sizeof(char*));
	
	if (create_stack->strings == NULL){
		free(create_stack);
		exit(OUT_OF_MEMORY);
	}
	
	create_stack->top = -1;
	
	return create_stack;
}

void destroy(Stack **stack){

	for (int i = 0; i < (*stack)->top; i++)
		free((*stack)->strings[i]);

	free((*stack)->strings);
	free(*stack);
	*stack = NULL;
}

void push(Stack *stack, char *new_string){

	if (stack->top != stack->size - 1){
		stack->top++;
		stack->strings[stack->top] = malloc(strlen(new_string) + 1);
		strcpy(stack->strings[stack->top], new_string);
		
	}
	else
	printf("Достигнут максимум\n");
}

char *pop(Stack *stack) {
	if (stack->top == -1) { 
		return NULL;
	}
	stack->top--;
	
	return stack->strings[stack->top];
}

void print(Stack *stack){
	printf("<-|");

	for (int i = stack->top; i >= 0; i--)
		printf(" %s|", stack->strings[i]);	

	printf("|");
	printf("\n");
}

void print_back(Stack *stack){
	if(stack->top != -1){
		int n = stack->top;
		printf("%s ", stack->strings[stack->top]);

		for (int i = 0; i < n; i++)
			printf("%s ", pop(stack));

		pop(stack);
		printf("\n");
	}
	else
        printf("Стек пуст!\n");
}

void clear_arr(Stack *stack){
	if(stack->top != -1){
		int n = stack->top;
		for (int i = 0; i < n; i++)
			pop(stack);
		pop(stack);
	}
	else
	printf("Стек пуст!\n");
}

