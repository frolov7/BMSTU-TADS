#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "arrwords.h"
#include "struc_data.h"
#include "funcs.h"
#include "sorts.h"

int main(){
    setbuf(stdout, NULL);
    int n;
    struct theatre_t arr[NMAX];
    FILE *file;
    file = fopen("first.txt","r"); // открываем файл на чтение и считывание указанное кол-во данных
    if(file == NULL){
        printf ("Can't open file.\n");
        return ERROR;
    }
    printf("This program works with a database of theater performances.\n"
            "We consider the data for work from the file\n"
            "How many lines to read(from 1 to 45): ");
    if (scanf("%d",&n) != 1 || n > 45 || n < 0){
        printf("INPUT ERROR\n");
        return ERROR;
    }
    else{
        int exit = 1;
        read_file(file,n,arr);
        fclose(file);
        while (exit != 0)
            exit = main_menu(&n,arr);
        if (exit == 0)
            printf("See you soon!");
    }
    return OK;
}

