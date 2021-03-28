#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "func.h"

int main(void){
    short int rc = 0;
    float_number number_1;
    printf("This program multiply only real numbers, To multiply integer numbers, input: +1.e+6 -35.3e+7. \n"
           "The number must be with sign :+13.e+4. \n"
           "Mantissa must begin with a significant number (cannot contain extra zeros) \n");
    printf("Enter REAL number : 0|  |                            |32     |39\n");
    printf("                Input:");

    rc = read_number(&number_1);

    if (rc != OK)
        return rc;
    normalization(&number_1);

    float_number number_2;
    printf("Enter REAL number : 0|  |                            |32     |39\n");
    printf("                Input:");

    rc = read_number(&number_2);

    if (rc != OK)
        return rc;

    normalization(&number_2);

    int result[60] = {0}, res_power, ind;
    rc = multiply(number_1, number_2, result, &res_power, &ind);

    if (rc != OK)
        return rc;
    print_result(number_1, number_2, result, res_power, ind);
    
    return rc;
}