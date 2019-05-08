
#ifndef BUS_H
#define BUS_H

#include <string>
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <pthread.h>
#include <queue>
#include "clock.h"
#include "dataMem.h"
#include "config.h"

struct task{
    int index;
    int data;
    int write;
    int id;
};

class Bus
{
  public:
    Bus(Clock *clk, DataMem *dataMem);
    int write=0;
    int data=0;
    int index=0;
    int id=0;
    std::queue<task> memQueue;  // peticiones de memoria hechas al bus
    std::queue<task> readQueue;  // respuestas de lectura de datos
    pthread_cond_t busCondMutex = PTHREAD_COND_INITIALIZER;

  private:
    Clock *clk;
    DataMem *dataMem;
    pthread_t threadBus;
    static void *start(void *ptr);
};

#endif