#include "../inc/io.h"

void free_stream(){
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
}

int input_range(int *const num, const int left, const int right){
	if (scanf("%d", num) != INPUT_ERROR){
		free_stream();
		return INPUT_ERROR;
	}

	if (*num < left || *num > right){
		free_stream();
		return INPUT_ERROR;
	}

	return SUCCESS;
}

uint64_t tick(void){
	uint32_t high, low;
	__asm__ __volatile__(
		"rdtsc\n"
		"movl %%edx, %0\n"
		"movl %%eax, %1\n"
		: "=r"(high), "=r"(low)::"%rax", "%rbx", "%rcx", "%rdx");

	uint64_t ticks = (uint64_t)high << 32 | low;

	return ticks;
}