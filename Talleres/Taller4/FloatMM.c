#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define SIZE1 5000
#define SIZE2 50000
#define SIZE3 500000

#define rowsize 25

long seed; /* converted to long for 16 bit WR*/
int ima[rowsize + 1][rowsize + 1], imb[rowsize + 1][rowsize + 1], imr[rowsize + 1][rowsize + 1];
float rma[rowsize + 1][rowsize + 1], rmb[rowsize + 1][rowsize + 1], rmr[rowsize + 1][rowsize + 1];
double start_time, run_time;

void Initrand()
{
    seed = 74755L; /* constant to long WR*/
}

int Rand()
{
    seed = (seed * 1309L + 13849L) & 65535L; /* constants to long WR*/
    return ((int)seed);                      /* typecast back to int WR*/
}

/* Multiplies two real matrices. */

void rInitmatrix(float m[rowsize + 1][rowsize + 1])
{
    int temp, i, j;
    for (i = 1; i <= rowsize; i++)
        for (j = 1; j <= rowsize; j++)
        {
            temp = Rand();
            m[i][j] = (float)(temp - (temp / 120) * 120 - 60) / 3;
        }
}

void rInnerproduct(float *result, float a[rowsize + 1][rowsize + 1], float b[rowsize + 1][rowsize + 1], int row, int column)
{
    /* computes the inner product of A[row,*] and B[*,column] */
    int i;
    *result = 0.0f;
    for (i = 1; i <= rowsize; i++)
        *result = *result + a[row][i] * b[i][column];
}

void runSerial(int run)
{
    int i, j;
    Initrand();
    rInitmatrix(rma);
    rInitmatrix(rmb);
    for (i = 1; i <= rowsize; i++)
        for (j = 1; j <= rowsize; j++)
            rInnerproduct(&rmr[i][j], rma, rmb, i, j);
}

void runParallel(int run)
{
    int i, j;
    Initrand();
    rInitmatrix(rma);
    rInitmatrix(rmb);
#pragma omp parallel for
    for (i = 1; i <= rowsize; i++)
        for (j = 1; j <= rowsize; j++)
            rInnerproduct(&rmr[i][j], rma, rmb, i, j);
}

void runHandler(int times, int type)
{
    start_time = omp_get_wtime();
    if (type)
    {
#pragma omp parallel for
        for (int i = 0; i < times; i++)
        {
            runParallel(i);
        }
    }
    else
    {
        for (int i = 0; i < times; i++)
        {
            runSerial(i);
        }
    }
    run_time = omp_get_wtime() - start_time;
    printf("********** Matrix Mul Operation Results ************* \n");
    if (type)
    {
        printf("Runtime With openMP: %f\t", run_time);
    }
    else
    {
        printf("Runtime With OUT openMP: %f\t", run_time);
    }
    printf("Times:%d \n", times);
}

int main()
{
    runHandler(SIZE1, 1);
    runHandler(SIZE1, 0);

    runHandler(SIZE2, 1);
    runHandler(SIZE2, 0);

    runHandler(SIZE3, 1);
    runHandler(SIZE3, 0);

    return 0;
}
