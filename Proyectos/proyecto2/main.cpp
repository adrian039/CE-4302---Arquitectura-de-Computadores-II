#include "clock.cpp"
#include "dataMem.cpp"
#include "instMem.cpp"
#include "vectorRegisters.cpp"
#include "scalarRegisters.cpp"
#include "bus.cpp"
#include "alu.cpp"
#include "execution.cpp"
#include "control.cpp"
#include "writeback.cpp"
// #include "tools/instTool.h"
// #include "tools/instTool.cpp"

int main()
{
    Clock *clk = new Clock();
    DataMem *dataMem = new DataMem(clk);
    InstMem *instMem = new InstMem(clk);
    Bus *bus = new Bus(clk, dataMem);
    Alu *alu1 = new Alu(clk);
    Alu *alu2 = new Alu(clk);
    Alu *alu3 = new Alu(clk);
    Alu *alu4 = new Alu(clk);
    VectorRegisters *vectReg = new VectorRegisters(clk);
    ScalarRegisters *scaReg = new ScalarRegisters(clk);
    Control *control = new Control(clk, instMem, vectReg, scaReg);
    Execution *execution = new Execution(clk, control, alu1, alu2, alu3, alu4);
    Writeback *writeback = new Writeback(clk, control, execution, vectReg, scaReg, dataMem);
    return 0;
}