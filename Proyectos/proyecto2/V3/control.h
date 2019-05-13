#ifndef CONTROL_H
#define CONTROL_H

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
#include "instMem.h"
#include "vectorRegisters.h"
#include "scalarRegisters.h"
#include "dataMem.h"
#include "config.h"

class Control
{
public:
    int *vectDataA = (int *)calloc(8, sizeof(int));
    int *vectDataB = (int *)calloc(8, sizeof(int));
    int *vector = (int *)calloc(8, sizeof(int));
    int resultReg = 0;
    int scaDataB = 0; // used for scalar register values or inmediates
    int scaIndex=0;
    int aluSelect = 0;
    int vectorFlag = 0;
    int ldFlag = 0;
    int stFlag = 0;
    int scaMovFlag = 0;
    int pc = 0;
    Control(Clock *clk_, InstMem *instMem_, VectorRegisters *vectRegs_, ScalarRegisters *scaRegs_, DataMem *dataMem_);
    pthread_cond_t controlCondMutex = PTHREAD_COND_INITIALIZER;
    pthread_cond_t controlExecutionCondMutex = PTHREAD_COND_INITIALIZER;

private:
    Clock *clk;
    InstMem *instMem;
    VectorRegisters *vectRegs;
    ScalarRegisters *scaRegs;
    DataMem *datMem;
    int instCounter = 0;
    void processInstruction(Control *ctrl);
    int getData(std::string data);
    pthread_t threadControl;
    static void *start(void *ptr);
};

#endif