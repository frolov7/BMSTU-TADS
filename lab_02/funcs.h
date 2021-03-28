#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX_STRLEN 255
#define MAX_S 30
#define NMAX 50
#define N1MAX 2000
#define N2MAX 900
#define ERROR 1
#define OK 0

void key_create(struct keys_t *key, struct theatre_t *arr, int n);
void sort_key_bubble(struct keys_t *key, int n);
void sort_key_inseration(struct keys_t *key, int n);
void read_file(FILE *f, int n, struct theatre_t *arr);
void print_structure(const struct theatre_t arr[], int n);
void musical_for_children(struct theatre_t arr[], int n);
void add_line(struct theatre_t *arr, int *n);
void delete_line(struct theatre_t *arr, int *n);
void print_keys(struct keys_t *key, int len);
void add_in_file(FILE *f,struct theatre_t *arr, int n);
int main_menu(int *n, struct theatre_t *arr);


#endif 
