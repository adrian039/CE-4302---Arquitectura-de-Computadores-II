#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define float double

#define rowsize 1300
long seed; /* converted to long for 16 bit WR*/
int ima[rowsize + 1][rowsize + 1], imb[rowsize + 1][rowsize + 1], imr[rowsize + 1][rowsize + 1];
float rma[rowsize + 1][rowsize + 1], rmb[rowsize + 1][rowsize + 1], rmr[rowsize + 1][rowsize + 1];

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

void Mm(int run)
{
    int i, j;
    double start_time, run_time;
    Initrand();
    rInitmatrix(rma);
    rInitmatrix(rmb);
    start_time = omp_get_wtime();
    for (i = 1; i <= rowsize; i++)
        for (j = 1; j <= rowsize; j++)
            rInnerproduct(&rmr[i][j], rma, rmb, i, j);
    printf("%f\n", rmr[run + 1][run + 1]);
    run_time = omp_get_wtime() - start_time;
    printf("Tiempo: %f\n", run_time);
}

int main()
{
    Mm(1);
}
