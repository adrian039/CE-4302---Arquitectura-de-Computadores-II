#ifndef WRITEBACK_H
#define WRITEBACK_H

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
#include "dataMem.h"
#include "execution.h"
#include "config.h"

class Writeback
{
public:
    int resultReg = 0;
    Writeback(Clock *clk_, Control *ctrl_, Execution *exe_, VectorRegisters *vecRegs_, ScalarRegisters *scaRegs_, DataMem *dataMem_);
    pthread_cond_t writebackCondMutex = PTHREAD_COND_INITIALIZER;

private:
    Clock *clk;
    Control *ctrl;
    Execution *exe;
    VectorRegisters *vecRegs;
    ScalarRegisters *scaRegs;
    DataMem *dataMem;
    pthread_t threadWriteback;
    static void *start(void *ptr);
};

#endif