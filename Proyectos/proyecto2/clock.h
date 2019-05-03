
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
    int clockControl = 0;
    pthread_mutex_t clockMutex = PTHREAD_MUTEX_INITIALIZER;
    pthread_cond_t clockCondMutex = PTHREAD_COND_INITIALIZER;

  private:
    static void *startClock(void *ptr);
    static void *clockController(void *ptr);
    pthread_t clockThread, controlThread;
};

#endif