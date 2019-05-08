#ifndef SCALARREGISTERS_H
#define SCALARREGISTERS_H

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

class ScalarRegisters
{
  public:
    int index=0;
    int value=0;
    int read=0;
    ScalarRegisters(Clock *clk);
    pthread_cond_t scalarRegisterCondMutex = PTHREAD_COND_INITIALIZER;
    pthread_cond_t scalarRegisterReadMutex = PTHREAD_COND_INITIALIZER;
    int *scalarRegs=(int*)calloc(10, sizeof(int));

  private:
    Clock *clk;
    int readScalar(int index);
    void writeScalar(int data, int index);
    pthread_t threadScalarReg;
    static void *start(void *ptr);
};

#endif