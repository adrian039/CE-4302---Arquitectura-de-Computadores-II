#include "alu.h"

Alu::Alu(Clock *clk_)
{
    clk = clk_;
    pthread_create(&threadAlu, 0, &Alu::start, (void *)this);
    pthread_detach(threadAlu);
}

int Alu::vadd(unsigned char dataA, unsigned char dataB)
{
     //std::cout<<"SUMA"<<std::endl;
    unsigned char res = dataA + dataB;
    return (int)res;
}
int Alu::vsub(unsigned char dataA, unsigned char dataB)
{
    //std::cout<<"RESTA"<<std::endl;
    unsigned char res = dataA - dataB;
    return (int)res;
}

int Alu::vxor(unsigned char dataA, unsigned char dataB)
{
    unsigned char res = dataA ^ dataB;
    // std::cout<<" DATA A: "<<(int)dataA<<std::endl;
    // std::cout<<" DATA B: "<<(int)dataB<<std::endl;
    // std::cout<<"XOR DATA: "<<(int)res<<std::endl;
    return (int)res;
}

int Alu::vmul(unsigned char dataA, unsigned char dataB)
{
    unsigned char res = dataA * dataB;
    return (int)res;
}

int Alu::vrot(unsigned char dataA, int number)
{
    // std::cout<<"VROT - DATAA: ";
    // std::cout<<(int)dataA<<" DATAB: "<<(int) dataB<<std::endl;
    //std::cout<<"VROT"<<std::endl;
    unsigned char res = (dataA >> number) | (dataA << (8 - number));
    return (int)res;
}

int Alu::vlrot(unsigned char dataA, int number)
{
    std::cout<<"VLROT"<<std::endl;
    unsigned char res = (dataA << number) | (dataA >> (8 - number));
    return (int)res;
}

void *Alu::start(void *ptr)
{
    Alu *inst = (Alu *)ptr;
    while (1)
    {
        // pthread_mutex_lock(&(inst->clk->clockMutex));
        // pthread_cond_wait(&(inst->aluCondMutex), &(inst->clk->clockMutex));
        pthread_mutex_lock(&(inst->aluMutex));
        pthread_cond_wait(&(inst->aluCondMutex), &(inst->aluMutex));
      //  std::cout<<"EMPIEZO"<<std::endl;
        switch (inst->aluControl)
        {
        case 1:
            inst->result = inst->vadd(inst->dataA, inst->dataB);
            break;
        case 2:
            inst->result = inst->vsub(inst->dataA, inst->dataB);
            break;
        case 3:
            inst->result = inst->vxor(inst->dataA, inst->dataB);
            break;
        case 4:
            inst->result = inst->vmul(inst->dataA, inst->dataB);
            break;
        case 5:
            inst->result = inst->vrot(inst->dataA, inst->dataB);
            break;
        case 6:
            inst->result = inst->vlrot(inst->dataA, inst->dataB);
            break;
        }
        pthread_cond_signal(&(inst->aluResultCondMutex));
        pthread_mutex_unlock(&(inst->aluMutex));
        // pthread_mutex_unlock(&(inst->clk->clockMutex));
      //  std::cout<<"EMPIEZO"<<std::endl;
    }
}