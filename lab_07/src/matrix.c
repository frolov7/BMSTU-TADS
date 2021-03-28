#include "../inc/matrix.h"

int graph_connected(matrix_t matrix){
	int *connected = calloc(matrix.size, sizeof(int));
	dfs(matrix, 0, connected);

	for (int i = 0; i < matrix.size; i++)
		if (!connected[i]){
			free(connected);
			return 0;
		}
	free(connected);

	return 1;
}

matrix_t *mat_create(const int size){
	matrix_t *matrix = malloc(sizeof(matrix_t));
	if (!matrix)
		return NULL;
	matrix->size = size;
	matrix->matrix = malloc(sizeof(int *) * size);
	if (!matrix->matrix){
		free(matrix);
		return NULL;
	}
	for (int i = 0; i < size; i++){
		matrix->matrix[i] = calloc(size, sizeof(int));
		if (!matrix->matrix[i]){
			for (int j = 0; j < i; j++)
				free(matrix->matrix[j]);
			free(matrix->matrix);
			free(matrix);

			return NULL;
		}
	}

	return matrix;
}

void mat_free(matrix_t *matrix){
	for (int i = 0; i < matrix->size; ++i)
		free(matrix->matrix[i]);
	free(matrix->matrix);
	free(matrix);
}

int mat_fill(matrix_t *const matrix){
	int ver1, ver2;

	while (1){
		int rc = input_range(&ver1, -1, matrix->size - 1);
		if (rc)
			return rc;
		if (ver1 == EOI)
			break;
		rc = input_range(&ver2, 0, matrix->size - 1);
		if (rc)
			return rc;

		if (ver1 == ver2)
			return ERROR_PAIR;

		matrix->matrix[ver1][ver2] = 1;
		matrix->matrix[ver2][ver1] = 1;
	}

	return SUCCESS;
}

void dfs(const matrix_t matrix, const int vertex, int *visited){
	visited[vertex] = 1;

	for (int i = 0; i < matrix.size; i++)
		if (matrix.matrix[vertex][i] && !visited[i])
			dfs(matrix, i, visited);
}