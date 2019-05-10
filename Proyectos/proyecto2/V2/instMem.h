
#ifndef INSTMEM_H
#define INSTMEM_H

#include <string>
#include <stdio.h>
#include <cstdio>
#include <unistd.h>
#include <iostream>
#include <pthread.h>
#include <fstream>
#include <sstream>
#include "clock.h"
#include "config.h"

class InstMem
{
public:
  InstMem(Clock *clk);
  int write = 0;
  int data = 0;
  int index = 0;
  int *instMemory = (int *)calloc(262144, sizeof(int)); //1MB
  pthread_mutex_t instMemMutex = PTHREAD_MUTEX_INITIALIZER;
  pthread_cond_t instMemoryCondMutex = PTHREAD_COND_INITIALIZER;
  pthread_cond_t instMemoryReadMutex = PTHREAD_COND_INITIALIZER;

private:
  Clock *clk;
  int readInst(int index);
  void writeInst(int data, int index);
  int bin2int(std::string binary);
  pthread_t threadInstMem;
  pthread_t threadInstMem1;
  static void *start(void *ptr);
  static void *fillMem(void *ptr);
};

#endif