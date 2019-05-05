
#ifndef INSTMEM_H
#define INSTMEM_H

#include <string>
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <pthread.h>
#include <sys/select.h>
#include <sys/types.h>
#include <sys/mman.h>
#include "clock.h"
#include "config.h"

class InstMem
{
  public:
    InstMem(Clock *clk);
    int write=0;
    int data=0;
    int index=0;
    int *instMemory=(int*)calloc(262144, sizeof(int)); //1MB
    pthread_cond_t instMemoryCondMutex = PTHREAD_COND_INITIALIZER;
    pthread_cond_t instMemoryReadMutex = PTHREAD_COND_INITIALIZER;

  private:
    Clock *clk;
    int readInst(int index);
    void writeInst(int data, int index);
    pthread_t threadInstMem;
    static void *start(void *ptr);
};

#endif