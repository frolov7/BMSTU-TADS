#ifndef IO_H
#define IO_H

#include <stdio.h>
#include <inttypes.h>

#define SUCCESS 0
#define INPUT_ERROR 1
#define ERROR_PAIR 2
#define EOI -1

void free_stream();
int input_range(int *const num, const int left, const int right);
uint64_t tick(void);

#endif