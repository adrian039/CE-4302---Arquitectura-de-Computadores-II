#include "clock.h"
#include "dataMem.h"
#include "instMem.h"
#include "vectorRegisters.h"
#include "scalarRegisters.h"
#include "bus.h"
#include "alu.h"
// #include "tools/instTool.h"
// #include "tools/instTool.cpp"

int main()
{
    Clock *clk = new Clock();
    DataMem *dataMem = new DataMem(clk);
    InstMem *instMem = new InstMem(clk);
    Bus *bus = new Bus(clk, dataMem);
    Alu *alu= new Alu(clk);
    // instMem->file();
    // InstTool *inst = new InstTool(instMem);
    VectorRegisters *vectReg = new VectorRegisters(clk);
    ScalarRegisters *scaReg = new ScalarRegisters(clk);
    return 0;
}