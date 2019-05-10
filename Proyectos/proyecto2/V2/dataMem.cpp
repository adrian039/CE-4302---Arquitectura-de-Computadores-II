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
        // std::cout << content << std::endl;
        // std::cout << "RESULT: " << inst->bin2int(content) << std::endl;
        int number;
        std::istringstream iss(content);
        iss >> number;
        inst->dataMemory[cont] = number;
        cont++;
    }
}

int DataMem::readData(int index)
{
    // std::cout<<"INDEX: "<<index<<"  - DATA: "<<dataMemory[index]<<std::endl;
    return dataMemory[index];
}

void DataMem::writeData(int data, int index)
{
    // std::cout<<"\nESCRIBIENDO"<<std::endl;
    // std::cout<<"INDEX: "<<index;
    // std::cout<<"     DATA: "<<data<<std::endl;
    dataMemory[index] = data;
}

void *DataMem::start(void *ptr)
{
    DataMem *inst = (DataMem *)ptr;
    while (1)
    {
        // pthread_mutex_lock(&(inst->clk->clockMutex));
        pthread_mutex_lock(&(inst->dataMemMutex));
        // pthread_cond_wait(&(inst->dataMemCondMutex), &(inst->clk->clockMutex));
        pthread_cond_wait(&(inst->dataMemCondMutex), &(inst->dataMemMutex));
        if (inst->write)
        {
            inst->writeData(inst->data, inst->index);
           // std::cout<<"JO"<<std::endl;
            // pthread_cond_signal(&(inst->dataMemWriteMutex));
        }
        else
        {
            inst->data = inst->readData(inst->index);
           //  std::cout<<"JA"<<std::endl;
            // pthread_cond_signal(&(inst->dataMemReadMutex));
        }
        pthread_cond_signal(&(inst->dataMemFinishMutex));
        // pthread_mutex_unlock(&(inst->clk->clockMutex));
        pthread_mutex_unlock(&(inst->dataMemMutex));
    }
}