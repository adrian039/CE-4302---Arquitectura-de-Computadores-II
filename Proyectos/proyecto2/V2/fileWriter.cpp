#include "fileWriter.h"

FileWriter::FileWriter(Clock *clk_, ScalarRegisters *scaRegs_, VectorRegisters *vecRegs_, InstMem *instMem_, DataMem *dataMem_, Alu *alu_)
{
    clk = clk_;
    this->scaRegs = scaRegs_;
    this->vecRegs = vecRegs_;
    this->instMem = instMem_;
    this->dataMem = dataMem_;
    this->alu = alu;
    pthread_create(&threadFileWriter, 0, &FileWriter::start, (void *)this);
    pthread_join(threadFileWriter, NULL);
}

void *FileWriter::start(void *ptr)
{
    FileWriter *inst = (FileWriter *)ptr;
    FILE *f;
    while (1)
    {
        pthread_mutex_lock(&(inst->clk->clockMutex));
        pthread_cond_wait(&(inst->clk->clockFileCondMutex), &(inst->clk->clockMutex));
        f = fopen("stats.csv", "a");
        fprintf(f, "%d,%d,%d,%d,%d,%d,%d,%d,%d\n", inst->instMem->instMemory[0], inst->instMem->instMemory[1], inst->instMem->instMemory[2], inst->instMem->instMemory[3],
                inst->instMem->instMemory[4], inst->instMem->instMemory[5], inst->instMem->instMemory[6], inst->instMem->instMemory[7], inst->instMem->instMemory[8]);
        fclose(f);
        pthread_mutex_unlock(&(inst->clk->clockMutex));
    }
    // f = fopen("stats.csv", "a");
    // fprintf(f, "%s,%s,%s,%s,%s,%s,%s,%s,%s\n", "DateTime", "Machine", "Port", "File", "Content-Type", "Size (bytes)", "Threads", "Cycles", "Duration (Seconds)");
    // fclose(f);
}