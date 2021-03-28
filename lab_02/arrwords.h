#ifndef _ARRWORDS_H
#define _ARRWORDS_H
#define MAX_STRLEN 255
#define MAX_S 30
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int is_separator(char ch);
int get_word_by_pos(const char *str, int *ibeg, int *iend);
int arrwords(char str1[MAX_STRLEN][MAX_S], const char *str);

#endif
