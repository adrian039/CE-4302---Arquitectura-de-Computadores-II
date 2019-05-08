#include "bus.h"

Bus::Bus(Clock *clk_, DataMem *dataMem_)
{
    clk = clk_;
    this->dataMem = dataMem_;
    pthread_create(&threadBus, 0, &Bus::start, (void *)this);
    pthread_detach(threadBus);
}

void *Bus::start(void *ptr)
{
    Bus *inst = (Bus *)ptr;
    while (1)
    {
        pthread_mutex_lock(&(inst->clk->clockMutex));
        pthread_cond_wait(&(inst->clk->clockBusCondMutex), &(inst->clk->clockMutex));
        if (inst->memQueue.size() > 0)
        {
            task t = inst->memQueue.front();
            inst->dataMem->data = t.data;
            inst->dataMem->index = t.index;
            inst->dataMem->write = t.write;
            if (t.write)
            {
                pthread_cond_signal(&(inst->dataMem->dataMemCondMutex));
            }
            else
            {
                pthread_cond_signal(&(inst->dataMem->dataMemCondMutex));
                pthread_cond_wait(&(inst->dataMem->dataMemReadMutex), &(inst->clk->clockMutex));
                sleep(0.5);
                t.data=inst->dataMem->data;
            }
            inst->readQueue.push(t);
            inst->memQueue.pop();
        }
        pthread_mutex_unlock(&(inst->clk->clockMutex));
    }
}