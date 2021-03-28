#ifndef _SORTS_H_
#define _SORTS_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void sort_key_bubble(struct keys_t *key, int n);
void sort_key_inseration(struct keys_t *key, int n);
void sort_arr_puzerek(struct theatre_t *arr, int n);
void printonestruct(struct theatre_t arr);
void sort_arr_withkeys(struct theatre_t *arr, int n);
void sort_arr_inseration(struct theatre_t *arr, int n);
void new_index(struct theatre_t *arr, int n);
int efficient();

#endif 
