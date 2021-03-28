#include "../inc/io.h"
#include "../inc/matrix.h"

void graph_export(matrix_t matrix);

int main(){
	setbuf(stdout, NULL);
	int size;

	printf("\nЗадание: определить, является ли связным заданный граф.\n\n");
	printf("Введите количество вершин графа: ");
	int rc = input_range(&size, 1, INT_MAX);
	if (rc){
		printf("Неверное значение! Попробуйте еще раз.\n");
		return rc;
	}

	matrix_t *matrix = mat_create(size); 
	printf("Введите номера связанных вершин:\n");
	printf("   *Для остановки введите (-1)\n");
	rc = mat_fill(matrix);
	if (rc){
		if (rc == INPUT_ERROR){ 
			printf("Ошибка ввода. Попробуйте еще раз.\n");
			mat_free(matrix);
			return rc;
		}
		if (rc == ERROR_PAIR){
			printf("Ошибка ввода. Одинаковые значения.\n");
			mat_free(matrix);
			return rc;
		}
	}

	uint64_t start, finish;
	start = tick();
	if (!graph_connected(*matrix))
		printf("Заданный граф не является связным.\n");
	else
		printf("Заданный граф связный.\n");
	
	finish = tick();
	graph_export(*matrix);

	printf("\n\nВремя выполнения алгоритма: %ju tick.\n", finish - start);

	return SUCCESS;
}

void graph_export(matrix_t matrix){
	FILE *export = fopen("graph.txt", "w");
	fprintf(export, "graph {\n");

	for (int i = 0; i < matrix.size; i++)
		for (int j = 0; j < matrix.size; j++)
			if (matrix.matrix[i][j])
				matrix.matrix[j][i] = 0;

	for (int i = 0; i < matrix.size; ++i){
		for (int j = 0; j < matrix.size; ++j)
			if (matrix.matrix[i][j])
				fprintf(export, "%d -- %d;\n", i, j);
		fprintf(export, "%d;\n", i);
	}

	fprintf(export, "}\n");
	fclose(export);

	system("dot -Tpng graph.txt -o graph.png");
}