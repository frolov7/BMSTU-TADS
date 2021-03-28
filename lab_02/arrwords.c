#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "arrwords.h"
#include "struc_data.h"
#include "funcs.h"
#include "sorts.h"

/* функция для выделения слова, возвращает целочисленное значение. */
int is_separator(char ch){
    char raz[10] = ",.: ;-!?";
    for (int i = 0; i < 10; i++)
        if (ch == raz[i])
            return ERROR;
    return OK;
}
int get_word_by_pos(const char *str, int *ibeg, int *iend){
    int i = *ibeg;
    while (str[i] && is_separator(str[i]))
        i++;
    if (str[i]){
        *ibeg = i;
        while (str[i] && !is_separator(str[i]))
            i++;
        *iend = i - 1;
        return ERROR;
    }
    return OK;
}
/* функция создает массив слов, возвращает количество выделенных слов */
int arrwords(char str1[MAX_STRLEN][MAX_S], const char *str){
    int ibeg = 0, iend,k = 0, p = 0, f;

    while (get_word_by_pos(str, &ibeg, &iend)){
        for (int i = ibeg; i < iend + 1; i++){
            str1[p][k] = str[i];
            k = k + 1;
            f = k;
        }
        str1[p][k] = '\0';
        if (strcmp(str1[p], "") == 0)
            p = p - 1;
        k = 0;
        ibeg = iend + 1;
        p = p + 1;
    }
    str1[p - 1][f - 1] = '\0';
    return p;
}
