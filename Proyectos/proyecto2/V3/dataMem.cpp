#include "dataMem.h"

DataMem::DataMem(Clock *clk_)
{
    clk = clk_;
    this->fillMem((void *)this);
    pthread_create(&threadDataMem, 0, &DataMem::start, (void *)this);
    pthread_detach(threadDataMem);
    // pthread_join(threadDataMem, NULL);
}

void *DataMem::fillMem(void *ptr)
{
    DataMem *inst = (DataMem *)ptr;
    std::ifstream file(imgPixelsFile);
    std::string content;
    int cont = 0;
    while (file >> content)
    {
        int number;
        std::istringstream iss(content);
        iss >> number;
        inst->dataMemory[cont] = number;
        cont++;
    }
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
        pthread_mutex_lock(&(inst->dataMemMutex));
        pthread_cond_wait(&(inst->dataMemCondMutex), &(inst->dataMemMutex));
        if (inst->write)
        {
            inst->writeData(inst->data, inst->index);
        }
        else
        {
            inst->data = inst->readData(inst->index);
        }
        pthread_cond_broadcast(&(inst->dataMemFinishMutex));
        pthread_mutex_unlock(&(inst->dataMemMutex));
    }
}