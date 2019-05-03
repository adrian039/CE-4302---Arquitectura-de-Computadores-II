#ifndef VECTORREGISTERS_H
#define VECTORREGISTERS_H

#include <string>
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <pthread.h>
#include <sys/select.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "clock.h"
#include "config.h"

class VectorRegisters
{
  public:
    int index = 0;
    int *value;
    int read = 0;
    VectorRegisters(Clock *clk);
    pthread_cond_t vectorRegisterCondMutex = PTHREAD_COND_INITIALIZER;
    pthread_cond_t vectorRegisterReadMutex = PTHREAD_COND_INITIALIZER;
    int vectorRegs[10][8];

  private:
    Clock *clk;
    int *readVector(int index);
    void writeVector(int *data, int index);
    pthread_t threadVectorReg;
    static void *start(void *ptr);
};

#endif