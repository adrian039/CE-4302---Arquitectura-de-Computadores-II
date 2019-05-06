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
#include "config.h"

class Control{
    public:
        Control(Clock *clk_, InstMem *instMem_, VectorRegisters *vectRegs_, ScalarRegisters *scaRegs_);
        pthread_cond_t controlCondMutex = PTHREAD_COND_INITIALIZER;

    private:
        Clock *clk;
        InstMem *instMem;
        VectorRegisters *vectRegs;
        ScalarRegisters *scaRegs;
        int instCounter=0;
        void processInstruction(Control *ctrl);
        int getData(std::string data);
        pthread_t threadControl;
        static void *start(void *ptr);
};

#endif