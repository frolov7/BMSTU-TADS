#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "io.h"

typedef struct{
	int size;
	int **matrix;
} matrix_t;

int graph_connected(matrix_t matrix);
matrix_t *mat_create(const int size);
void mat_free(matrix_t *matrix);
int mat_fill(matrix_t *const matrix);
void dfs(const matrix_t matrix, const int vertex, int *visited);

#endif