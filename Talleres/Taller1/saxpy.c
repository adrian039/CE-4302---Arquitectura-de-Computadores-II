#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

const int vectSize = 50000000;

void saxpy(int n, float a, int *restrict x, int *restrict y)
{
    int *res;
   res = malloc (sizeof(int) * vectSize);
   for (int i = 0; i < n; ++i)
   {
      res[i] = a * x[i] + y[i];
      //printf("Prueba:%d\n", y[i]);
   }
}

int main()
{
    int *v1, *v2;
   v1=malloc(sizeof(int) * vectSize);
   v2=malloc(sizeof(int) * vectSize);
   double start_time, run_time;
  
   for (int i = 0; i < vectSize; i++)
   {
      v1[i] = rand() % 4096;
      v2[i] = rand() % 4096;
   }
    start_time = omp_get_wtime();
   saxpy(vectSize, 12.5, v1, v2);
   run_time = omp_get_wtime() - start_time;
   printf("Tiempo: %f\n", run_time);
}

// Perform SAXPY on 1M elements
//saxpy(1<<20, 2.0, x, y);