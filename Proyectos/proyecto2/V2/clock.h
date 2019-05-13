
#ifndef CLOCK_H
#define CLOCK_H

#include <string>
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <pthread.h>
#include <sys/select.h>
#include "config.h"

class Clock
{
public:
  Clock();
  int counter = 0;
  int clockFlag=0;
  int clockControl = 0;
  int *instructions = (int *)calloc(262144, sizeof(int)); //1MB
  pthread_mutex_t clockMutex = PTHREAD_MUTEX_INITIALIZER;
  pthread_cond_t clockCondMutex = PTHREAD_COND_INITIALIZER;
  pthread_cond_t clockBusCondMutex = PTHREAD_COND_INITIALIZER;
  pthread_cond_t clockControlCondMutex = PTHREAD_COND_INITIALIZER;
  pthread_cond_t scalarRegisterCondMutex = PTHREAD_COND_INITIALIZER;
  pthread_cond_t clockAluCondMutex = PTHREAD_COND_INITIALIZER;
  pthread_cond_t clockWritebackCondMutex = PTHREAD_COND_INITIALIZER;
  pthread_cond_t memoriesDataInitMutex = PTHREAD_COND_INITIALIZER;
  pthread_cond_t clockExecuteCondMutex = PTHREAD_COND_INITIALIZER;
  pthread_cond_t clockControlWriteMutex = PTHREAD_COND_INITIALIZER;
  pthread_cond_t clockFileCondMutex = PTHREAD_COND_INITIALIZER;

private:
  static void *startClock(void *ptr);
  static void *clockController(void *ptr);
  pthread_t clockThread, controlThread;
};

#endif