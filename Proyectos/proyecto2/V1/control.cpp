#include "control.h"

Control::Control(Clock *clk_, InstMem *instMem_, VectorRegisters *vectRegs_, ScalarRegisters *scaRegs_)
{
    clk = clk_;
    this->instMem = instMem_;
    this->vectRegs = vectRegs_;
    this->scaRegs = scaRegs_;
    pthread_create(&threadControl, 0, &Control::start, (void *)this);
    pthread_detach(threadControl);
}

int Control::getData(std::string data)
{
    int output = std::stoi(data, nullptr, 2);
    return output;
}

void *Control::start(void *ptr)
{
    Control *inst = (Control *)ptr;
    while (1)
    {
        pthread_mutex_lock(&(inst->clk->clockMutex));
        pthread_cond_wait(&(inst->clk->clockControlCondMutex), &(inst->clk->clockMutex));
        if (inst->instMem->instMemory[inst->pc] != 0)
        {
            std::cout << "FETCH STARTED" << std::endl;
            std::bitset<24> b;
            b = (std::bitset<24>)inst->instMem->instMemory[inst->pc];
            std::string instruction = b.to_string();
            int opcode = inst->getData(instruction.substr(0, 5));
            int datA = 0;
            int datB = 0;
            int datR = 0;
            int *vecDataA = (int *)calloc(8, sizeof(int));
            int *vecDataB = (int *)calloc(8, sizeof(int));
            //  pthread_cond_wait(&(inst->clk->clockCondMutex), &(inst->clk->clockMutex)); // ***** PIPELINE BEHAVIOR *****//
            std::cout << "DECODE STARTED" << std::endl;
            if (opcode == 0 || opcode == 3 || opcode == 6 || opcode == 9)
            {
                inst->vectorFlag = 1;
                datA = inst->getData(instruction.substr(10, 5));
                datB = inst->getData(instruction.substr(15, 5));
                datR = inst->getData(instruction.substr(5, 5));
                inst->resultReg = datR;
                inst->vectRegs->index = datA;
                inst->vectRegs->read = 1;
                pthread_cond_signal(&(inst->vectRegs->vectorRegisterCondMutex));
                pthread_cond_wait(&(inst->vectRegs->vectorRegisterReadMutex), &(inst->clk->clockMutex));
                inst->vectRegs->read = 0;
                inst->vectDataA = inst->vectRegs->value;
                inst->vectRegs->index = datB;
                inst->vectRegs->read = 1;
                pthread_cond_signal(&(inst->vectRegs->vectorRegisterCondMutex));
                pthread_cond_wait(&(inst->vectRegs->vectorRegisterReadMutex), &(inst->clk->clockMutex));
                inst->vectRegs->read = 0;
                inst->vectDataB = inst->vectRegs->value;
                switch (opcode)
                {
                case 0:
                    inst->aluSelect = 1;
                    break;
                case 3:
                    inst->aluSelect = 2;
                    break;
                case 6:
                    inst->aluSelect = 3;
                    break;
                case 9:
                    inst->aluSelect = 4;
                    break;
                }
                //pthread_cond_wait(&(inst->clk->clockCondMutex), &(inst->clk->clockMutex)); // ***** PIPELINE BEHAVIOR *****//
                pthread_cond_signal(&(inst->controlExecutionCondMutex));
            }
            else if (opcode == 2 || opcode == 5 || opcode == 8 || opcode == 11)
            {
                inst->vectorFlag = 0;
                datA = inst->getData(instruction.substr(10, 5));
                datB = inst->getData(instruction.substr(15, 5));
                datR = inst->getData(instruction.substr(5, 5));
            }
            else if (opcode == 1 || opcode == 4 || opcode == 7 || opcode == 12 || opcode == 13)
            {
                inst->vectorFlag = 0;
                datA = inst->getData(instruction.substr(10, 5));
                datB = inst->getData(instruction.substr(15, 9));
                datR = inst->getData(instruction.substr(5, 5));
            }
            else if (opcode == 10 || opcode == 14 || opcode == 15 || opcode == 16)
            {
                inst->vectorFlag = 0;
                datA = inst->getData(instruction.substr(10, 14));
                datR = inst->getData(instruction.substr(5, 5));
                inst->resultReg = datR;
                if (opcode == 14)
                {
                    // std::cout << "STORE DETECTED" << std::endl;
                    inst->stFlag = 1;
                    inst->ldFlag = 0;
                    inst->vectRegs->read=1;
                    pthread_cond_signal(&(inst->vectRegs->vectorRegisterCondMutex));
                    pthread_cond_wait(&(inst->vectRegs->vectorRegisterReadMutex), &(inst->clk->clockMutex));
                    inst->vector=inst->vectRegs->value;
                    inst->scaDataB = datA;
                    pthread_cond_signal(&(inst->clk->clockWritebackCondMutex));
                }
                else if (opcode == 15)
                {
                    // std::cout << "LOAD DETECTED - INDEX: " <<datA <<std::endl;
                    inst->ldFlag = 1;
                    inst->stFlag = 0;
                    inst->scaDataB = datA;
                    pthread_cond_signal(&(inst->clk->clockWritebackCondMutex));
                }
            }
        }
        else
        {
            std::cout << "INSTRUCTIONS EMPTY..." << std::endl;
            // instructions completed!
        }
        inst->pc++;
        pthread_mutex_unlock(&(inst->clk->clockMutex));
    }
}