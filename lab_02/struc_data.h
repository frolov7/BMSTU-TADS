#ifndef _STRUCT_H_
#define _STRUCT_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NMAX 50

//структура для хранения данных о театре
struct theatre_t{
    int number;
    char name[30]; //название театра
    char performance[30];//спектакль
    char producer[30];// режиссер
    int low_price;// нижняя цена
    int high_price;//верхняя цена
    int flag;
    union{
        struct{
            int year;//возраст
            char type_for_child[30];//тип детского спектакля
        } children;
        struct{
           char type_for_adult[30];//тип взрослого спекткаля
        } adult;
        struct{
            char composer[30];//композитор
            char country[30];//страна
            int min_year; // минимальный возраст
            int duration; // продолжительность
        } music;
    }staff;
};
//структура для хранения ключей
struct keys_t{
    int ID;
    int pricelow;
};


#endif 
