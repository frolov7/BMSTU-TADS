#ifndef FUNC_H
#define FUNC_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#define INT_MAX 33
#define OK 0
#define NO_POINT -1
#define OK_READ 1
#define ERR_UNRIGHT_MANTISS_SIGN -1
#define ERR_UNRIGHT_MANTISS_NUM -2
#define ERR_NO_EPSILON -3
#define ERR_TOO_MUCH_POINTS -4
#define ERR_ONLY_POINT -5
#define ERR_MANTISSA_TOO_LONG -6
#define ERR_NUMBER_MUST_BE_FLOAT -7
#define ERR_UNRIGHT_POWER_SIGN -8
#define ERR_UNRIGHT_POWER -9
#define ERR_POWER_TOO_LONG -10
#define ERR_NO_NUMBER -11
#define ERR_POWER_OVERFLOW -12
typedef struct{
    char mantis_sign;
    char mantissa[INT_MAX + 1];
    char eps_sign;
    int eps_num;
    int point_place;
    int num_of_digits;
} float_number;

short int read_number(float_number *number);
void swap(char *mantissa, int j);
void swap1(char *mantissa, int j);
void delete_num(char *mantissa, int *n, int i);
unsigned short int move_arr(char *arr, int n);
void append(char *arr, int n, int i, char elm);
void normalization(float_number *number);
void check_arr(int *arr, int ind, int end_arr);
int find_power(float_number num1, float_number num2, int extra_power);
short int multiply(float_number num1, float_number num2, int *result, int *res_power, int *ind);
void print_result(float_number num1, float_number num2, int *result, int res_power, int ind);

#endif
