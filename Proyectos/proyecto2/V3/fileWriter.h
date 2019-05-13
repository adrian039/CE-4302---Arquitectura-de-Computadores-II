#ifndef FILEWRITER_H
#define FILEWRITER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include "scalarRegisters.h"
#include "vectorRegisters.h"
#include "instMem.h"
#include "dataMem.h"
#include "alu.h"
#include "config.h"

class FileWriter
{
  public:
    FileWriter(Clock *clk_, ScalarRegisters *scaRegs_, VectorRegisters *vecRegs_, InstMem *instMem_, DataMem *dataMem_, Alu *alu_);

  private:
    Clock *clk;
    ScalarRegisters *scaRegs;
    VectorRegisters *vecRegs;
    InstMem *instMem;
    DataMem *dataMem;
    Alu *alu;
    pthread_t threadFileWriter;
    static void *start(void *ptr);
};

#endif