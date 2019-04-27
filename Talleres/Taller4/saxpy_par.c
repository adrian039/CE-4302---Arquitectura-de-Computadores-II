#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
#include <arm_neon.h>

#define VEC1SIZE 800000
#define VEC2SIZE 8000000
#define VEC3SIZE 80000000
#define MAXNUM 32765

double start_time, run_time;

void execSaxpy(int size)
{
    start_time = omp_get_wtime();

    int *vecR, *vecA, *vecB, *vecC;
    vecA = (int *)calloc(size, sizeof(int));
    vecB = (int *)calloc(size, sizeof(int));
    vecC = (int *)calloc(size, sizeof(int));
    for (int i = 0; i < size; i++)
    {
        vecA[i] = rand() % MAXNUM;
        vecB[i] = rand() % MAXNUM;
        vecC[i] = rand() % MAXNUM;
    }
    int16x8_t v1;
    int16x8_t v2;
    int16x8_t v3;
    #pragma omp for
    for (int i = 0; i < size; i += 8)
    {
        v1 = vld1q_s16(vecA);
        v2 = vld1q_s16(vecB);
        v3 = vld1q_s16(vecC);
        int16x8_t res = vmlaq_s16(v1, v2, v3);
        vecA += 8;
        vecB += 8;
        vecC += 8;
    }

    free(*vecA);
    free(*vecB);
    free(*vecC);
    run_time = omp_get_wtime() - start_time;
    printf("Result *********************** \n");
    printf("Vector Size:%d \t", size);
    printf("Runtime:%f \t", run_time);
    printf("\n");
}

int main()
{
    execSaxpy(VEC1SIZE);
    execSaxpy(VEC2SIZE);
    execSaxpy(VEC3SIZE);
    return 0;
}