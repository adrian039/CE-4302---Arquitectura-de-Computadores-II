
#include "vectorRegisters.h"

VectorRegisters::VectorRegisters(Clock *clk_)
{
    clk = clk_;
    pthread_create(&threadVectorReg, 0, &VectorRegisters::start, (void *)this);
    pthread_detach(threadVectorReg);
    // pthread_join(threadVectorReg, NULL);
}

int *VectorRegisters::readVector(int index)
{
    int *data=(int*)calloc(8, sizeof(int));
    for (int i = 0; i < 8; i++)
    {
        data[i] = vectorRegs[index][i];
    }
    return data;
}

void VectorRegisters::writeVector(int *data, int index)
{
    for (int i = 0; i < 8; i++)
    {
        std::cout<<"DATA "<<i<<": "<<data[i]<<std::endl;
        vectorRegs[index][i] = data[i];
    }
}

void *VectorRegisters::start(void *ptr)
{
    VectorRegisters *inst = (VectorRegisters *)ptr;
    while (1)
    {
        pthread_mutex_lock(&(inst->clk->clockMutex));
        pthread_cond_wait(&(inst->vectorRegisterCondMutex), &(inst->clk->clockMutex));
        if (inst->read)
        {
            // std::cout << "LEEEOOOO" << std::endl;
            inst->value = inst->readVector(inst->index);
            pthread_cond_signal(&(inst->vectorRegisterReadMutex));
        }
        else
        {
            inst->writeVector(inst->value, inst->index);
            pthread_cond_signal(&( inst->vectorRegisterWriteMutex));
        }
        pthread_mutex_unlock(&(inst->clk->clockMutex));
    }
}