#ifndef EXECUTION_H
#define EXECUTION_H

#include <string>
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <functional>
#include <bitset>
#include <sstream>
#include <pthread.h>
#include "clock.h"
#include "control.h"
#include "alu.h"
#include "vectorRegisters.h"
#include "scalarRegisters.h"
#include "config.h"

class Execution
{
public:
  int *vectDataA = (int *)calloc(8, sizeof(int));
  int *vectDataB = (int *)calloc(8, sizeof(int));
  int *result = (int *)calloc(8, sizeof(int));
  int resultReg = 0;
  int scaDataB = 0; // used for scalar register values or inmediates
  int aluControl = 0;
  int dataA1 = 0, dataA2 = 0, dataA3 = 0, dataA4 = 0;
  int dataB1 = 0, dataB2 = 0, dataB3 = 0, dataB4 = 0;
  Execution(Clock *clk_, Control *control_, Alu *alu1_, Alu *alu2_, Alu *alu3_, Alu *alu4_);
  pthread_cond_t executionCondMutex = PTHREAD_COND_INITIALIZER;

private:
  Clock *clk;
  Control *ctrl;
  Alu *alu1, *alu2, *alu3, *alu4;
  pthread_t threadExecution;
  static void *start(void *ptr);
};

#endif