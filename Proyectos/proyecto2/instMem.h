
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
    int *instMemory=(int*)calloc(262144, sizeof(int)); //1MB

  private:
    Clock *clk;
    int readInst(int index);
    pthread_t threadInstMem;
    static void *start(void *ptr);
};

#endif