#include "func.h"
// умножение матрицы хранящейся в связанном списке и вектора столбца
void multiplicate(int n, int *A, int *JA, int *IA, int *x, int *b) {
    for (int i = 0; i < n; i++) {
        b[i] = 0;
        for (int j=IA[i]; j < IA[i + 1]; j++)
            b[i] += A[j] * x[JA[j]];
    }
}
void new_mult(int *A, int size_a, int *IA, int *JA, int size_ja, int *res_new, int *vector) {
    int k = 0, el, num;
    for (int i = 0; i < size_ja - 1; i++) {
        res_new[k] = 0;
        if (JA[i] == JA[i + 1])
            res_new[k] = 0;
        else {
            for (int j = JA[i]; j < JA[i + 1]; j++) {
                el = A[j];
                num = IA[j];
                res_new[k] += el * vector[num];
            }
        }
        k += 1;
    }
}
// ввод матриц ручной
int mtr_input(int a[][NMAX], int *n, int *m) {
    int rc = OK;
    printf("Input size of matrix n x m:");
    if (scanf ("%d %d", n, m) == 2) {
        if (1 <= *n  && 1 <= *m ) {
            printf("Input elements:");
            for (int i = 0; rc == OK && i < *n; i++)
                for (int j = 0; rc == OK && j < *m; j++)
                    if (scanf("%d", &a[i][j]) != 1)
                        rc = ERR_IO;
        }
        else
            rc = ERR_IO;
    }
    else
        rc = ERR_RANGE;
    return rc;
}
// выввод матрицы ручной 
void mtr_print(int a[][NMAX], int n, int m) {
    printf("Matrix \n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++)
            printf("%d ", a[i][j]);
        printf("\n");
    }
}
// умножение обычное
void multiply_basic(int a[][NMAX], int n, int m,int *b,int c[][NMAX]) {
    
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            c[i][j] = 0;
            for(int k = 0; k < m; k++)
                c[i][j] += a[i][k] * b[k];
        }
    }
}
// печать массива 
void print_array(int *mtr, int len) {
    for (int i = 0; i < len; i++)
        printf("%d ", mtr[i]);
    printf("\n");
}
//преобразование в связанный список матрицы
void convert_matrix(const int matr[][NMAX], int n, int m, int *A, int *JA, int *IA, int *count) {
    int no_zero_e = 0;
    int A_curr = 0;
    int first_in_row = 1;
    for (int i = 0; i < n; i++) {
        first_in_row = 1;
        for (int j = 0; j < m; j++) {
            if (matr[i][j] != 0) {
                A[A_curr] = matr[i][j];
                JA[A_curr] = j;
                no_zero_e++;
                if (first_in_row) {
                    first_in_row = 0;
                    IA[i] = A_curr;
                }
                A_curr++;
            }
            if (first_in_row == 1) {
                IA[i] = no_zero_e;
            }
       }
    }
    IA[n] = no_zero_e;
    *count = A_curr;
}
// ввод вектора столбца
int arr_input(int *a, int *n) {
    printf("Input number of elements: ");
    if (scanf("%d", n) != 1)
        return ERR_IO;
    if (*n <= 0 || *n > NMAX)
        return ERR_RANGE;
    printf("Input elements: \n");
    for (int i = 0; i < *n; i++)
        if (scanf("%d", &a[i]) != 1)
            return ERR_IO;
    return OK;
}
// ввод вектора столбца
int array(int *a, int n) {
    printf("Input elements: ");
    for (int i = 0; i < n; i++)
        if (scanf("%d", &a[i]) != 1)
            return ERR_IO;
    return OK;
}
// гененрирование матрицы с определенным процентом кол-ва целых
void generate_matrix(int matr[][NMAX], int n, int m, int fill) {
    int count = n*m * (fill / 100.0); //такое кол-во ненулевых элементов должно быть
    int inew, jnew;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
                matr[i][j] = 0;
    for(int k = 0; k < count; k ++) {
        inew = rand()%n;
        jnew = rand()%m;
        if (matr[inew][jnew] == 0)
            matr[inew][jnew]= rand()%9 + 1;
        else
            k--;
    }
}
//для выввода времени в тиках
unsigned long long tick(void) {
    unsigned long long tmp;
    __asm__ __volatile__ ("rdtsc" : "=A" (tmp) );
    return tmp;
}
// генерирование вектора столбца с определенным кол-вом целых
void generate_array(int *x, int n, int fill) {
    int count = n * (fill / 100.0), jnew;
    for(int i = 0; i < n; i++)
            x[i] = 0;
    for(int j = 0; j < count; j++) {
        jnew = rand()%n;
        if (x[jnew] == 0)
            x[jnew]= rand()%9 + 1;
        else
            j--;
    }
}

int input_pos_element(int n, int m, int *b, int *bj, int *bi, int *b_n) {
    printf("Input number of NONE ZERO elements: ");
    if (scanf("%d", b_n) != 1)
        return ERR_IO;
    if (*b_n <= 0 || *b_n > n*m)
        return ERR_RANGE;
    for (int i = 0; i < *b_n; i++) {
        printf("First the value, then the position (for matrix): ");
        if (scanf("%d %d %d", &b[i], &bi[i], &bj[i]) != 3 )
            return ERR_IO;
        if(bi[i] >= n || bj[i] >= m)
            return ERR_IO;
    }
    return OK;
}
int input_arr_with_pos(int m, int *b, int *bj, int *b_n) {
    printf("Input number of NONE ZERO elements in column: ");
    if (scanf("%d", b_n) != 1)
        return ERR_IO;
    if (*b_n <= 0 || *b_n > m)
        return ERR_RANGE;
    printf("For example: vector column is: 2 0 0 5\n You should input: \n 2 0 \n 5 3 \n");
    for (int i = 0; i < *b_n; i++) {
        printf("First the value, then the position(for vector): ");
        if (scanf("%d %d", &b[i], &bj[i]) != 2) {
            printf("Input error");
            return ERR_IO;
        }
        if(bj[i] >= m)
            return ERR_IO;
    }
    return OK;
}
void make_matrix(int a[][NMAX], int n, int m,int *b, int *bi, int *bj, int n_m) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            a[i][j] = 0;
    for (int k =0; k < n_m; k++)
        a[bi[k]][bj[k]] = b[k];
}
void make_array(int *a, int n, int *b, int *bi, int n_m) {
    for (int i = 0; i < n; i++)
            a[i] = 0;
    for (int k =0; k < n_m; k++)
        a[bi[k]] = b[k];
}
void efficient()
{
    FILE *f = fopen("efficient.txt","r");
    char s[70];
    while(!feof(f))
    {
        fgets(s,70,f);
        printf("%s",s);
    }
    fclose(f);
}