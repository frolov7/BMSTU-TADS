#include "func.h"
void menu()
{
    printf("This program will calculate multiply of int matrix and vector column.\n"
            "How do you want to enter the matrix\n 1. By hand \n 2. Auto \n 3. Only none zero elements\n 4. Print efficient\n"); 
}

int main(void) {
	setbuf(stdout, NULL);
    int rc = OK;
    int a[NMAX][NMAX], n_a, m_a;
    int c1[NMAX][NMAX], c2[NMAX];
    int a1[NMAX], count,count1;
    int ja1[NMAX],jc1[NMAX];
    int ia1[NMAX],ic1[NMAX];
    int x[NMAX], x_n;
    int fillm, fill;
    int flag, flag1;
    printf("This program will calculate multiply of int matrix and vector column.\n"
            "How do you want to enter the matrix\n 0 - EXIT\n 1. By hand \n 2. Auto \n 3. Only none zero elements\n 4. Print efficient\n");
    while (scanf("%d", &flag) != 0)
    {
        if (flag == 0)
            return 0;
        else if (flag == 1) {
           rc = mtr_input(a, &n_a, &m_a);
           if (rc == OK) {
               printf("Input  %d column elements:\n", m_a);
               x_n = m_a;
               rc = array(x, x_n);
           }

        }
        else if(flag == 3) {
            int b[NMAX], b_n;
            int bj[NMAX], bi[NMAX];
            int xval[NMAX], xj[NMAX], d;
            printf("Input size of matrix n x m:");
            if (scanf ("%d %d", &n_a, &m_a) != 2)
                rc = ERR;
            else {
                rc = input_pos_element(n_a, m_a, b,bj,bi, &b_n);
                if (rc == OK) {
                    make_matrix(a,n_a, m_a,b,bi,bj,b_n);
                    x_n = m_a;
                    rc = input_arr_with_pos(m_a, xval, xj, &d);
                    make_array(x, m_a, xval, xj, d);
                }
            }
        }
        else if (flag == 2) {
            printf("Input size of matrix n x m:");
            if (scanf ("%d %d", &n_a, &m_a) != 2)
                rc = ERR;
            printf("Input percentage of none zero elements in matrix: \n");
            if (scanf("%d", &fillm) != 1)
                rc = ERR;
            x_n = m_a;
            printf("Input percentage of none zero elements in vector column: \n");
            if (scanf("%d", &fill) != 1)
                 rc = ERR;
            generate_matrix(a, n_a, m_a, fillm);
            generate_array(x, x_n, fill);
        }
        else if (flag == 4)
        {
            int option;
            efficient();
            return 0;
            //printf("\nWould you like to continue?\n 1 - YES\n");
            /*
            if (scanf("%d", &option) == 1)
            {
                printf("This program will calculate multiply of int matrix and vector column.\n"
                        "How do you want to enter the matrix\n 1. By hand \n 2. Auto \n 3. Only none zero elements\n 4. Print efficient\n");
                scanf("%d", &flag);
                if (rc == OK) {
                    if (flag == 1) {
                       rc = mtr_input(a, &n_a, &m_a);
                       if (rc == OK) {
                           printf("Input  %d column elements:\n", m_a);
                           x_n = m_a;
                           rc = array(x, x_n);
                       }
                    }
                    else if(flag == 3) {
                        int b[NMAX], b_n;
                        int bj[NMAX], bi[NMAX];
                        int xval[NMAX], xj[NMAX], d;
                        printf("Input size of matrix n x m:");
                        if (scanf ("%d %d", &n_a, &m_a) != 2)
                            rc = ERR;
                        else {
                            rc = input_pos_element(n_a, m_a, b,bj,bi, &b_n);
                            if (rc == OK) {
                                make_matrix(a,n_a, m_a,b,bi,bj,b_n);
                                x_n = m_a;
                                rc = input_arr_with_pos(m_a, xval, xj, &d);
                                make_array(x, m_a, xval, xj, d);
                            }
                        }
                    }
                    else if (flag == 2) {
                        printf("Input size of matrix n x m:");
                        if (scanf ("%d %d", &n_a, &m_a) != 2)
                            rc = ERR;
                        printf("Input percentage of none zero elements in matrix: \n");
                        if (scanf("%d", &fillm) != 1)
                            rc = ERR;
                        x_n = m_a;
                        printf("Input percentage of none zero elements in vector column: \n");
                        if (scanf("%d", &fill) != 1)
                             rc = ERR;
                        generate_matrix(a, n_a, m_a, fillm);
                        generate_array(x, x_n, fill);
                    }
               }
            }
            else if (option == 2)
                return 0;
                */
        }
        else {
            printf("Input ERROR(you can choose 1, 2 , 3 only)\n");
            rc = ERR;
        }
        if (rc == OK) {
            convert_matrix(a, n_a, m_a, a1, ja1, ia1, &count);
            printf("Do you want to print matrix and columnvector? \n1. Yes\n2.No\n");
            scanf("%d", &flag1);
            if(flag1 == 1){
                mtr_print(a, n_a, m_a);
                printf("Print A:");
                print_array(a1,count);
                printf("Print JA:");
                print_array(ja1,count);
                printf("Print IA:");
                print_array(ia1, n_a+1);
                printf("Print column vector:");
                print_array(x, x_n);
            }
            int c[n_a];

            unsigned long long time_beg, time_end, time_res = 0;
            unsigned long long time_beg1, time_end1, time_res1 = 0;
            for (int i = 0 ; i < 30; i++) {
                time_beg1 = tick();
                multiply_basic(a, n_a, m_a,x,c1);
                time_end1 = tick();
                time_res1 += (time_end1 - time_beg1);
            }
            for (int i = 0 ; i < 30; i++) {
                time_beg = tick();
                multiplicate(n_a, a1, ja1, ia1, x, c);
                time_end = tick();
                time_res += (time_end - time_beg);
            }

            printf("Result of multiply: \n");
            print_array(c,n_a);
            mtr_print(c1, n_a, 1);
            convert_matrix(c1, n_a, 1, c2, jc1, ic1, &count1);
            printf("Print A:");
            print_array(c2,count1);
            printf("Print JA:");
            print_array(jc1,count1);
            printf("Print IA:");
            print_array(ic1, n_a+1);
            //printf("Method with ja runtime: %I64u\n", time_res/30);
            //printf("Size of IA: %I64u  \n", (2*count + n_a+1)*sizeof(int));
            //printf("Simple Method with runtime: %I64u\n", time_res1/30);
            //printf("Size of mtr: %I64u  \n", sizeof(int)*n_a*m_a);            
        }
        else
            printf("Input ERROR\n");
                menu();
    }
    printf("Thanks!");
    return rc;
}
