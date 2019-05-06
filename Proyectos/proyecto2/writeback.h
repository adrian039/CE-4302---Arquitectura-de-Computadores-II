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
#include "instMem.h"
#include "vectorRegisters.h"
#include "scalarRegisters.h"
#include "config.h"

class Writeback{
    public:
        Writeback(Clock *clk_);
        pthread_cond_t writebackCondMutex = PTHREAD_COND_INITIALIZER;

    private:
        Clock *clk;
        pthread_t threadWriteback;
        static void *start(void *ptr);
};

#endif