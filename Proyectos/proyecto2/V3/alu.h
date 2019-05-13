
#ifndef ALU_H
#define ALU_H

#include <string>
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <pthread.h>
#include <queue>
#include "clock.h"
#include "config.h"

class Alu
{
  public:
    Alu(Clock *clk);
    int aluControl=0;
    int dataA=0;
    int dataB=0;
    int result=0;
    pthread_cond_t aluCondMutex = PTHREAD_COND_INITIALIZER;
    pthread_cond_t aluResultCondMutex = PTHREAD_COND_INITIALIZER;

  private:
    Clock *clk;
    int vadd(unsigned char dataA, unsigned char dataB);
    int vsub(unsigned char dataA, unsigned char dataB);
    int vxor(unsigned char dataA, unsigned char dataB);
    int vmul(unsigned char dataA, unsigned char dataB);
    int vrot(unsigned char dataA, int number);
    int vlrot(unsigned char dataA, int number);
    pthread_t threadAlu;
    static void *start(void *ptr);
};

#endif