#ifndef FUNC_H
#define FUNC_H

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define NMAX 500
#define OK 0
#define ERR_IO 1
#define ERR_RANGE 2
#define ERR 3

void multiplicate(int n, int *A, int *JA, int *IA, int *x, int *b);
void new_mult(int *A, int size_a, int *IA, int *JA, int size_ja, int *res_new, int *vector);
int mtr_input(int a[][NMAX], int *n, int *m);
void mtr_print(int a[][NMAX], int n, int m);
void multiply_basic(int a[][NMAX], int n, int m,int *b,int c[][NMAX]);
void print_array(int *mtr, int len);
void convert_matrix(const int matr[][NMAX], int n, int m, int *A, int *JA, int *IA, int *count);
int arr_input(int *a, int *n);
int array(int *a, int n);
void generate_matrix(int matr[][NMAX], int n, int m, int fill);
unsigned long long tick(void);
void generate_array(int *x, int n, int fill);
int input_pos_element(int n, int m, int *b, int *bj, int *bi, int *b_n);
int input_arr_with_pos(int m, int *b, int *bj, int *b_n);
void make_matrix(int a[][NMAX], int n, int m,int *b, int *bi, int *bj, int n_m);
void make_array(int *a, int n, int *b, int *bi, int n_m);
void efficient();

#endif