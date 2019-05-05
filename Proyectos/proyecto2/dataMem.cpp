#include "dataMem.h"

DataMem::DataMem(Clock *clk_)
{
    clk = clk_;
    pthread_create(&threadDataMem, 0, &DataMem::start, (void *)this);
    pthread_detach(threadDataMem);
    // pthread_join(threadDataMem, NULL);
}

int DataMem::readData(int index)
{
    return dataMemory[index];
}

void DataMem::writeData(int data, int index)
{
    dataMemory[index] = data;
}

void *DataMem::start(void *ptr)
{
    DataMem *inst = (DataMem *)ptr;
    while (1)
    {
        pthread_mutex_lock(&(inst->clk->clockMutex));
        pthread_cond_wait(&(inst->dataMemCondMutex), &(inst->clk->clockMutex));
        if (inst->write)
        {
            inst->writeData(inst->data, inst->index);
        }
        else
        {
            inst->data = inst->readData(inst->index);
            pthread_cond_signal(&(inst->dataMemReadMutex));
        }
        pthread_mutex_unlock(&(inst->clk->clockMutex));
    }
}