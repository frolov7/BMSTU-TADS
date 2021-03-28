#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "arrwords.h"
#include "struc_data.h"
#include "funcs.h"
#include "sorts.h"

// Считывание данных из файла
void read_file(FILE *f, int n, struct theatre_t *arr){
    char str[255];
    char str1[MAX_STRLEN + 1][MAX_S];
    int i = 0;
    while (i < n){
        if (fgets(str,255,f) != NULL){
            arrwords(str1, str);
            arr[i].number = i + 1;
            strcpy(arr[i].name, str1[1]);
            strcpy(arr[i].performance, str1[2]);
            strcpy(arr[i].producer, str1[3]);
            arr[i].low_price = atoi(str1[4]);
            arr[i].high_price = atoi(str1[5]);
            arr[i].flag = atoi(str1[6]);
            if (arr[i].flag == 1){
                arr[i].staff.children.year = atoi(str1[7]);
                strcpy(arr[i].staff.children.type_for_child , str1[8]);
            }
            else if (arr[i].flag == 2){
                strcpy(arr[i].staff.adult.type_for_adult , str1[7]);
            }
            else{
                strcpy(arr[i].staff.music.composer,str1[7]);
                strcpy(arr[i].staff.music.country , str1[8]);
                arr[i].staff.music.min_year = atoi(str1[9]);
                arr[i].staff.music.duration = atoi(str1[10]);
            }
            i++;
        }
    }
}
// Функция для вывода основной таблицы
void print_structure(const struct theatre_t arr[], int n){
    printf("n  |Name of theatre|  Performance  |   Producer    |Pricelow |   Pricehigh|   Type      |Year|Typechild |Typeadult|   Composer   |"
           "    Country    |Minyear|Duration|\n");
    printf("-----------------------------------------------------------------------------------------------------------------------------"
           "-------------------------------------|\n");
    for (int i = 0 ; i<n; i++){
        printf("%-3d|%-15s|%-15s|%-15s|%8d |%9d   |", arr[i].number, arr[i].name, arr[i].performance,arr[i].producer,arr[i].low_price,
        arr[i].high_price);
        if (arr[i].flag == 1){
           printf("for children |%-4d|%-10s|         |              |               |       |        |\n",arr[i].staff.children.year, arr[i].staff.children.type_for_child);
        }
        else if (arr[i].flag == 2){
            printf("for adult    |    |          |%-9s|              |               |       |        |\n",arr[i].staff.adult.type_for_adult);
        }
        else{
            printf("music        |    |          |         |%-14s|%-15s|%-7d|%-8d|\n",arr[i].staff.music.composer,arr[i].staff.music.country,arr[i].staff.music.min_year,arr[i].staff.music.duration);

        }
        printf("------------------------------------------------------------------------------------------------------------------------"
              "------------------------------------------|\n");
    }
}
// Функция для добавления записи в структуру 
void add_line(struct theatre_t *arr, int *n){
    arr[*n].number = *n + 1;
    printf("Input the name of Theatre: \n");
    scanf("%s", arr[*n].name);

    printf("Input the name of Performance: \n");
    scanf("%s", arr[*n].performance);

    printf("Input the name of Producer: \n");
    scanf("%s", arr[*n].producer);

    printf("Input the lowest price: \n");
    scanf("%d", &arr[*n].low_price);

    printf("Input the highest price: \n");
    scanf("%d", &arr[*n].high_price);

    printf("What type of performance?(input 1,2 or 3)\n1. Children \n2. Adult\n3. Musical \n");
    scanf("%d", &arr[*n].flag);

    if (arr[*n].flag == 1){
        printf("Input the minimal age:\n");
        scanf("%d", &arr[*n].staff.children.year);
        printf("What type of children perfomance?(write in words)\n1. fairytale\n2. play\n3. musical\n");
        if(scanf("%s", arr[*n].staff.children.type_for_child) != 1)
            printf("WRONG input");
    }
    else if(arr[*n].flag == 2){
        printf("What type of adult perfomance?(write in words)\n1. drama\n2. comedy\n3. play\n");
        if(scanf("%s", arr[*n].staff.adult.type_for_adult) != 1)
            printf("WRONG input");
    }
    else{
        printf("Input the name of Composer: \n");
        scanf("%s", arr[*n].staff.music.composer);
        printf("Input the name of Country: \n");
        scanf("%s", arr[*n].staff.music.country );
        printf("Input the minimal age:\n");
        scanf("%d", &arr[*n].staff.music.min_year);
        printf("Input the duration of performance:\n");
        scanf("%d", &arr[*n].staff.music.duration);
    }
    *n = *n + 1;
}
// Функция для удаления записи в структуре 
void delete_line(struct theatre_t *arr, int *n){
    int dell;
    printf("Enter the number of the line you want to delete:");
    if (scanf("%d", &dell)!=1)
        printf("INPUT_ERROR\n");
    if (dell > *n)
         printf("No such index\n");
    dell = dell - 1;
    for (int i = dell ; i < *n-1; i++)
    {
        arr[i] = arr[i+1];
    }
    *n = *n - 1;
}
// Функция для замены индексов в таблице 
void new_index(struct theatre_t *arr, int n){
    for (int i = 0 ; i < n; i++){
        arr[i].number = i+1;
    }
}

// Вывод списка всех музыкальных спектаклей для детей указанного возраста и меньше указанной продолжительности 
void musical_for_children(struct theatre_t arr[], int n){
    int age, dur, flag = 0, j = 0;
    printf("Enter age: \n");
    if (scanf("%d",&age)!=1)
        printf("INPUT_ERROR \n");
    else{
        printf("Enter max duration: \n");
        if (scanf("%d",&dur) != 1)
            printf("INPUT_ERRORR \n");
        else{
            for (int i=0; i<n; i++)
                 if (arr[i].flag == 3){
                    if (arr[i].staff.music.min_year <= age){
                        if (arr[i].staff.music.duration < dur){
                            printf("%d : %-3d|%-15s|%-15s|%-15s|%8d|%9d|%-14s|%-15s|%-7d|%-8d|\n", j+1, arr[i].number, arr[i].name, arr[i].performance,arr[i].producer,arr[i].low_price,
                                   arr[i].high_price, arr[i].staff.music.composer,arr[i].staff.music.country,arr[i].staff.music.min_year,arr[i].staff.music.duration);
                            flag = 1;
                            j++;
                        }
                    }
                 }
            if (flag == 0)
                printf("No music perfomance for you \n");
        }
    }
}
// Заполнение таблицы ключей 
void key_create(struct keys_t *key, struct theatre_t *arr, int n){
    for (int i = 0; i < n; i++){
        key[i].ID = arr[i].number;
        key[i].pricelow = arr[i].low_price;
    }
}

// Функция для замера времени 
int efficient(){
    struct theatre_t arr1[N1MAX];
    struct theatre_t arr2[N2MAX];

    struct keys_t key1[N1MAX];
    struct keys_t key2[N2MAX];

    struct theatre_t arr3[N1MAX];
    struct theatre_t arr4[N2MAX];

    struct keys_t key3[N1MAX];
    struct keys_t key4[N2MAX];

    FILE *file1, *file2;
    file1 = fopen("theathre_1.txt","r");
    file2 = fopen("theathre_2.txt","r");

    if((file1 == NULL || file2 == NULL)){
        printf ("Cannot open file.\n");
        return ERROR;
    }

    read_file(file1,N1MAX,arr3);
    read_file(file2,N2MAX,arr4);
    read_file(file1,N1MAX,arr1);
    read_file(file2,N2MAX,arr2);

    fclose(file1);
    fclose(file2);

    key_create(key1, arr1, N1MAX);
    key_create(key2, arr2, N2MAX);
    key_create(key3, arr3, N1MAX);
    key_create(key4, arr4, N2MAX);

    clock_t tb1 = 0, te1 = 0;
    tb1 = clock();
    sort_key_bubble(key1,N1MAX);
    te1 = clock();

    clock_t start1 = clock();
    sort_arr_puzerek(arr1,N1MAX);
    clock_t cend1 = clock();

    clock_t tb2 = 0, te2 = 0;
    tb2 = clock();
    sort_key_bubble(key2,N2MAX);
    te2 = clock();

    clock_t start2 = clock();
    sort_arr_puzerek(arr2,N2MAX);
    clock_t cend2 = clock();


    clock_t tb3 = 0, te3 = 0;
    tb3 = clock();
    sort_key_inseration(key3,N1MAX);
    te3 = clock();

    clock_t start3 = clock();
    sort_arr_inseration(arr3,N1MAX);
    clock_t cend3 = clock();


    clock_t tb4 = 0, te4 = 0;
    tb4 = clock();
    sort_key_inseration(key4,N2MAX);
    te4 = clock();

    clock_t start4 = clock();
    sort_arr_inseration(arr4,N2MAX);
    clock_t cend4 = clock();

    printf("\n_________________________________| Keys       | Table    |\n");
    printf("TIME of inser sort %4d elements : %6fs  | %6fs| \n", N1MAX, difftime(te3, tb3)/CLK_TCK, difftime(cend3,start3)/CLK_TCK);
    printf("TIME of buble sort %4d elements : %6fs  | %6fs| \n", N1MAX, difftime(te1, tb1)/CLK_TCK, difftime(cend1, start1)/CLK_TCK);
    printf("TIME of inser sort %4d elements : %6fs  | %6fs| \n", N2MAX, difftime(te4, tb4)/CLK_TCK, difftime(cend4,start4)/CLK_TCK);
    printf("TIME of buble sort %4d elements : %6fs  | %6fs| \n", N2MAX, difftime(te2, tb2)/CLK_TCK, difftime( cend2,start2)/CLK_TCK);
    return 0;

}
// Функция для вывода ключей
void print_keys(struct keys_t *key, int len){
    printf("Sorted keys(the table has not changed)\n");
    printf("|i  |new|lowprices|\n");
    printf("|-----------------|\n");
    for (int i =0 ; i < len; i++){
        printf("|%3d|%3d|%9d|\n",i+1, key[i].ID, key[i].pricelow);
        printf("|-----------------|\n");
    }
}

// Функция для вывода исходной таблицы в упорядоченном виде, используя упорядоченную таблицу ключей
void printonestruct(struct theatre_t arr){
    printf("%-3d|%-15s|%-15s|%-15s|%8d|%9d|", arr.number, arr.name, arr.performance,arr.producer,arr.low_price,
              arr.high_price);
    if (arr.flag == 1){
        printf("for children |%-4d|%-10s|         |              |               |       |        |\n",arr.staff.children.year, arr.staff.children.type_for_child);
    }
    else if(arr.flag == 2){
        printf("for adult    |    |          |%-9s|              |               |       |        |\n",arr.staff.adult.type_for_adult);
    }
    else{
        printf("music        |    |          |         |%-14s|%-15s|%-7d|%-8d|\n",arr.staff.music.composer,arr.staff.music.country,arr.staff.music.min_year,arr.staff.music.duration);

    }
    printf("------------------------------------------------------------------------------------------------------------------------"
              "--------------------------------------|\n");
}

// Функция для добавления записи в файл
void add_in_file(FILE *f,struct theatre_t *arr, int n){
    char str[255];
    char num1[5], num2[5], num3[5], num4[5], num5[5], num6[5];
    for(int i=0; i<n;i++){
        strcat(str, ltoa(arr[i].number,num1,10));
        strcat(str, " ");
        strcat(str, arr[i].performance);
        strcat(str, " ");
        strcat(str, arr[i].producer);
        strcat(str, " ");
        strcat(str, ltoa(arr[i].low_price,num2,10));
        strcat(str, " ");
        strcat(str, ltoa(arr[i].high_price,num3,10));
        strcat(str, " ");
        strcat(str, ltoa(arr[i].flag,num4,10));
        if (arr[i].flag == 1){
            strcat(str, " ");
            strcat(str, arr[i].staff.children.type_for_child);
        }
        else if (arr[i].flag == 2){
            strcat(str, " ");
            strcat(str, arr[i].staff.adult.type_for_adult);
        }
        else{
            strcat(str, " ");
            strcat(str, arr[i].staff.music.composer);
            strcat(str, " ");
            strcat(str, arr[i].staff.music.country);
            strcat(str, " ");
            strcat(str, ltoa(arr[i].staff.music.min_year, num5,10));
            strcat(str, " ");
            strcat(str, ltoa(arr[i].staff.music.duration, num6,10));
        }
        strcat(str, "\n");
        fwrite (&str, sizeof(int),1, f);
        strcpy(str, " ");
    }
}
// Основное меню для работы с таблицей
int main_menu(int *n, struct theatre_t *arr){
    int input;
    struct keys_t key[N1MAX];
    printf( "1. Print table.\n"
            "2. Add new note.\n"
            "3. Delete note. \n"
            "4. Musical performances for age .. less than duration ..\n"
            "5. Viewing a sorted key table with an unsorted table.\n"
            "6. Sort table. \n"
            "7. Sort table with keys. \n"
            "8. The efficient of program.\n"
            "0. Exit.\n");
    printf("Input:");
    scanf("%d",&input);
    if (input == 1)
        print_structure(arr, *n);
    else if (input == 2)
        add_line(arr, n);
    else if (input == 3){
        delete_line(arr, n);
        new_index(arr, *n);
    }
    else if (input == 4)
        musical_for_children(arr, *n);
    else if (input == 5){
        key_create(key, arr, *n);
        sort_key_bubble(key, *n);
        print_keys(key, *n);
    }
    else if (input == 6){
        sort_arr_inseration(arr, *n);
        new_index(arr, *n);
    }
    else if (input == 7)
        sort_arr_withkeys(arr, *n);
    else if (input == 8)
        efficient();
    else if (input == 0)
        return OK;
    return ERROR;
}