#include "clock.h"
#include "scalarRegisters.h"
#include "vectorRegisters.h"

int main()
{
    Clock *clk = new Clock();
    ScalarRegisters *scaReg = new ScalarRegisters(clk);
   // VectorRegisters *vectReg = new VectorRegisters(clk);
    return 0;
}