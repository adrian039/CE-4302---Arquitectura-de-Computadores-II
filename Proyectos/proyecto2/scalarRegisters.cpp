
#include "scalarRegisters.h"

ScalarRegisters::ScalarRegisters(Clock *clk_)
{
    clk = clk_;
    pthread_create(&threadScalarReg, 0, &ScalarRegisters::start, (void *)this);
    pthread_join(threadScalarReg, NULL);
}

int ScalarRegisters::readScalar(int index)
{
    return scalarRegs[index];
}

void ScalarRegisters::writeScalar(int data, int index)
{
    scalarRegs[index] = data;
}

void *ScalarRegisters::start(void *ptr)
{
    ScalarRegisters *inst = (ScalarRegisters *)ptr;
    while (1)
    {
        pthread_mutex_lock(&(inst->clk->clockMutex));
        pthread_cond_wait(&(inst->scalarRegisterCondMutex), &(inst->clk->clockMutex));
        if (inst->read)
        {
            inst->value = inst->readScalar(inst->index);
            pthread_cond_signal(&(inst->scalarRegisterReadMutex));
        }
        else
        {
            inst->writeScalar(inst->value, inst->index);
        }
        pthread_mutex_unlock(&(inst->clk->clockMutex));
    }
}