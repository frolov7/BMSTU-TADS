#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "arrwords.h"
#include "struc_data.h"
#include "funcs.h"
#include "sorts.h"

//сортировка ключей пузыркем
void sort_key_bubble(struct keys_t *key, int n){
    for (int i = 0; i < n; i++){
        for (int j = i+1; j < n; j++){
            if (key[i].pricelow > key[j].pricelow){
                struct keys_t tmp;
                tmp = key[i];
                key[i] = key[j];
                key[j] = tmp;
            }
        }
    }
}
//сортировка ключей вставками
void sort_key_inseration(struct keys_t *key, int n){
    for (int i = 1; i < n; i++){
        struct keys_t tmp = key[i];
        int ind = i;
        while (ind > 0 && key[ind-1].pricelow > tmp.pricelow){
            key[ind] = key[ind-1];
            ind--;
        }
    key[ind] = tmp;
    }
}

//сортировка таблицы пузырьком
void sort_arr_puzerek(struct theatre_t *arr, int n){
    for(int i = 0 ; i < n-1; i++){
        for(int j = 0 ; j < n - i - 1; j++){
            if (arr[j].low_price > arr[j+1].low_price){
                struct theatre_t tmp = arr[j];
                arr[j] = arr[j+1] ;
                arr[j+1] = tmp;
            }
        }
    }
}
void sort_arr_withkeys(struct theatre_t *arr, int n){
    int pos, kluchi[NMAX], kluchinew[NMAX];
    for (int i =0 ; i < n; i++){
        kluchi[i]=arr[i].low_price;
        kluchinew[i] = i + 1;
    }
    for(int i = 0 ; i < n-1; i++){
        for(int j = 0 ; j < n - i - 1 ; j++){
            if (kluchi[j] > kluchi[j+1]){
                int tmp = kluchi[j];
                int tmp2 = kluchinew[j];
                kluchi[j] = kluchi[j+1] ;
                kluchi[j+1] = tmp;
                kluchinew[j] = kluchinew[j+1] ;
                kluchinew[j+1] = tmp2;
            }
         }
    }
    for(int i = 0; i < n; i++){
        pos = kluchinew[i] - 1;
        printonestruct(arr[pos]);
    }
}
//сортировка таблицы вставками
void sort_arr_inseration(struct theatre_t *arr, int n){
    int location, new1;
    struct theatre_t newElement;
    for (int i = 1; i < n; i++){
        new1 = arr[i].low_price;
        newElement = arr[i];
        location = i - 1;
        while(location >= 0 && arr[location].low_price > new1){
            arr[location+1].number = arr[location].number;
            arr[location+1] = arr[location];
            location = location - 1;
         }
         arr[location+1].number = new1;
         arr[location+1] = newElement;
    }
}
