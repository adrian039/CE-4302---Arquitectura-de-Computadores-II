#include "instMem.h"

InstMem::InstMem(Clock *clk_)
{
    clk = clk_;
    pthread_create(&threadInstMem, 0, &InstMem::start, (void *)this);
    pthread_detach(threadInstMem);
    // pthread_join(threadInstMem, NULL);
}

int InstMem::readInst(int index)
{
    return instMemory[index];
}

void InstMem::writeInst(int data, int index)
{
    instMemory[index] = data;
}

void *InstMem::start(void *ptr)
{
    InstMem *inst = (InstMem *)ptr;
    while (1)
    {
        pthread_mutex_lock(&(inst->clk->clockMutex));
        pthread_cond_wait(&(inst->instMemoryCondMutex), &(inst->clk->clockMutex));
        if (inst->write)
        {
            inst->writeInst(inst->data, inst->index);
        }
        else
        {
            inst->data = inst->readInst(inst->index);
            pthread_cond_signal(&(inst->instMemoryReadMutex));
        }
        pthread_mutex_unlock(&(inst->clk->clockMutex));
    }
}