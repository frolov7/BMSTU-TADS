#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "func.h"

/* Функция считывает две строки, которые содержат вещественные
числа, и записывает части числа в нужные места структуры  */
short int read_number(float_number *number){
    int c;
    if ((c = getchar()) != '\n'){
        if ((c == EOF) || strchr("+-", c) == NULL){   
            puts("Incorrect input.");
            return ERR_UNRIGHT_MANTISS_SIGN;
        }

        number->mantis_sign = c;
    }
    else{
        puts("Incorrect input.");
        return ERR_NO_NUMBER;
    }
    int i = 0;
    number->point_place = NO_POINT;

    while ((c = getchar()) != 'e'){
        if ((c == EOF) || (c == '\n')){   
            puts("ERROR: NO_EPSILON");
            return ERR_NO_EPSILON;
        }

        if ((c == '.') && (number->point_place == NO_POINT))
            number->point_place = i;
        else if ((c == '.') && (number->point_place != NO_POINT)){
            puts("Incorrect input.");
            return ERR_TOO_MUCH_POINTS;            
        }

        if ((c != '.') && (strchr("0123456789", c) == NULL)){
            puts("Incorrect input.");
            return ERR_UNRIGHT_MANTISS_NUM;
        }

        number->mantissa[i++] = c;

        if (i > INT_MAX){
            puts("ERROR: MANTISSA_ TOO_LONG");
            return ERR_MANTISSA_TOO_LONG;
        }
    }

    number->num_of_digits = i - 1;
    number->mantissa[i] = '\0';

    if (number->point_place == NO_POINT){
        puts("Incorrect input.");
        return ERR_NUMBER_MUST_BE_FLOAT;        
    }

    if (number->num_of_digits == 0){
        puts("ERROR: ONLY_POINT");
        return ERR_ONLY_POINT;
    }
    // Read Power Sign
    if ((c = getchar()) != '\n'){
        if ((c == EOF) || (strchr("+-", c) == NULL)){   
            puts("ERROR: ONLY_POINT");
            return ERR_UNRIGHT_POWER_SIGN;
        }

        number->eps_sign = c;
    }
    // Read Power Sign
    int num;
    if (scanf("%d", &num) != 1){
        puts("Incorrect input.");
        return ERR_UNRIGHT_POWER;
    }
    else if (num / 100000 >= 1){
        puts("ERROR: POWER_TOO_LONG");
        return ERR_POWER_TOO_LONG;
    }

    c = getchar();
    if ((c != EOF) && (c != '\n')){
        puts("Incorrect input.");
        return ERR_UNRIGHT_POWER;
    }
    else
        number->eps_num = num;
    return OK;
}
void swap(char *mantissa, int j){
    char tmp = mantissa[j];
    mantissa[j] = mantissa[j + 1];
    mantissa[j + 1] = tmp;
}
void swap1(char *mantissa, int j){
    char tmp = mantissa[j];
    mantissa[j] = mantissa[j - 1];
    mantissa[j - 1] = tmp;
}
void delete_num(char *mantissa, int *n, int i){
    for (int j = i; j < *n; j++)
        swap(mantissa, j);
}
unsigned short int move_arr(char *arr, int n){
    unsigned short int k = 0;
    for (int j = n; j > 0; j--){
        swap1(arr, j);
        k++;
    }
    return k;
}
void append(char *arr, int n, int i, char elm){
    char tmp = arr[i];
    arr[i] = elm;
    for (int j = i + 1; j <= n; j++){
        char cur = arr[j];
        arr[j] = tmp;
        tmp = cur;
    }
}
/* Функция убирает ненужные нули и сдвигает точку в
начало числа, изменяя его порядок.*/
void normalization(float_number *number){
    int n = number->num_of_digits;
    //Do not count 0 in the end
    while(number->mantissa[n--] == '0')
        number->num_of_digits--;

    n = number->num_of_digits;
    
    if (number->mantissa[0] == '0'){
        int i = 0;
        while (strchr("123456789.", number->mantissa[i]) == NULL){
            delete_num(number->mantissa, &n, i);
            number->point_place -= 1;
            number->num_of_digits -= 1;
        }
    }

    if (number->mantissa[0] != '0'){
        unsigned short int k;

        k = move_arr(number->mantissa, number->point_place);
        number->point_place -= k;
        
        if (number->eps_sign == '+'){
            number->eps_num += k;
        }
        else{
            number->eps_num -= k;
        }
    }

    if ((number->mantissa[number->point_place + 1] == '0') && (number->mantissa[number->point_place] == '.')){
        int i = number->point_place + 1;

        int q = 0; 

        while ((number->mantissa[i] == '0') && (q++ < INT_MAX)){
            delete_num(number->mantissa, &n, i);
            number->num_of_digits -= 1;

            if (number->eps_sign == '+')
                number->eps_num -= 1;
            else
                number->eps_num += 1;
        }

        // SPECIAL FOR 0
        if (number->num_of_digits < 0)
            number->num_of_digits = 1;
    }
}
/* Удаляет лишние нули или округляет число*/
void check_arr(int *arr, int ind, int end_arr){
    if (arr[end_arr + 1] >= 5){
        int i = end_arr;
        while (arr[i] == 9){
            arr[i] = (arr[i] + 1) % 10;
            i--;
        }
        arr[i] = (arr[i] + 1) % 10;
    }
}

int find_power(float_number num1, float_number num2, int extra_power){
    int power_1, power_2, res_power;

    if (num1.eps_sign == '-')
        power_1 = num1.eps_num * (-1); 
    else
        power_1 = num1.eps_num;
    
    if (num2.eps_sign == '-')
        power_2 = num2.eps_num * (-1);
    else
        power_2 = num2.eps_num;

    res_power = power_1 + power_2 + extra_power;

    return res_power;
}

/* функцию умножения. Функция создает массив максимально
возможной длины числа с элементами типа int и производит умножение в столбик*/
short int multiply(float_number num1, float_number num2, int *result, int *res_power, int *ind){
    int n1 = num1.num_of_digits;
    int n2 = num2.num_of_digits;
    
    int index = 59, q;
    
    int num, write, rem = 0;
    
    for (int i = n1; i > 0; i--){
        q = index;
        rem = 0;
        
        for (int j = n2; j > 0; j--){
            num = (num1.mantissa[i] - '0') * (num2.mantissa[j] - '0') + rem + result[q];
            
            write = num % 10;
            rem = num / 10;
            
            result[q] = write;
            q--;
        }
        
        index--;
        result[q] = rem;
    }

    int extra_power = 0;

    if (result[q] != 0)
        *ind = q;
    else{
        *ind = q + 1;
        extra_power = -1;
    }
    
    *res_power = find_power(num1, num2, extra_power);

    if (*res_power > 99999){
        puts("ERROR: Overflow");
        return ERR_POWER_OVERFLOW;
    }

    return 0;
}
/* Функция вывода результата.*/
void print_result(float_number num1, float_number num2, int *result, int res_power, int ind){
    char res_sign_mantis;

    if (num1.mantis_sign != num2.mantis_sign){
        res_sign_mantis = '-';
    }
    else{
        res_sign_mantis = '+';
    }
    char res_sign_eps;
    if (res_power < 0){
        res_power *= -1;
        res_sign_eps = '-';
    }
    else
        res_sign_eps = '+';

    if (result[ind] != 0){
        printf("\nResult : %c0.", res_sign_mantis);

        int end_arr = 60;

        if (end_arr - ind > 30 ){
            end_arr -= (end_arr - ind - 29);
            check_arr(result, ind, end_arr);
        }

        int j = end_arr;

        if (result[j] == 0)
            while (result[j--] == 0)
                end_arr--;

        if (end_arr != 60)
            end_arr += 1;

        for (int i = ind; i < end_arr; i++)
            printf("%d", result[i]);
        printf("e%c%d\n", res_sign_eps, res_power);
    }
    else
        puts("\n\nResult : +0.0e+0\n");
}