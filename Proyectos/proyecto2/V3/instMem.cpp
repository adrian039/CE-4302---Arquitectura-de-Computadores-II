#include "instMem.h"

InstMem::InstMem(Clock *clk_)
{
    clk = clk_;
    this->fillMem((void *)this);
    pthread_create(&threadInstMem, 0, &InstMem::start, (void *)this);
    pthread_detach(threadInstMem);
    // pthread_join(threadInstMem, NULL);
}

void *InstMem::fillMem(void *ptr)
{
    InstMem *inst = (InstMem *)ptr;
    std::ifstream file(instFile);
    std::string content;
    int cont = 0;
    while (file >> content)
    {
        inst->instMemory[cont] = inst->bin2int(content);
        cont++;
    }
    pthread_cond_broadcast(&(inst->clk->memoriesDataInitMutex));
}

int InstMem::bin2int(std::string binary)
{
    int output = std::stoi(binary, nullptr, 2);
    return output;
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