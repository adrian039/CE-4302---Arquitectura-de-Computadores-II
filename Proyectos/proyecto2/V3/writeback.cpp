#include "writeback.h"

Writeback::Writeback(Clock *clk_, Control *ctrl_, Execution *exe_, VectorRegisters *vecRegs_, ScalarRegisters *scaRegs_, DataMem *dataMem_)
{
    clk = clk_;
    this->ctrl = ctrl_;
    this->exe = exe_;
    this->vecRegs = vecRegs_;
    this->scaRegs = scaRegs_;
    this->dataMem = dataMem_;
    pthread_create(&threadWriteback, 0, &Writeback::start, (void *)this);
    pthread_detach(threadWriteback);
    // pthread_join(threadWriteback, NULL);
}

void *Writeback::start(void *ptr)
{
    Writeback *inst = (Writeback *)ptr;
    while (1)
    {
        pthread_mutex_lock(&(inst->clk->clockMutex));
        pthread_cond_wait(&(inst->clk->clockWritebackCondMutex), &(inst->clk->clockMutex));
        if(!inst->clk->clockControl)
            std::cout << "WRITEBACK STARTED" << std::endl;
        if (inst->ctrl->ldFlag)
        {
            inst->dataMem->write = 0;
            int *vector = (int *)calloc(8, sizeof(int));
            for (int i = 0; i < 8; i++)
            {
                inst->dataMem->index = inst->ctrl->scaDataB + i;
                pthread_cond_signal(&(inst->dataMem->dataMemCondMutex));
                // pthread_cond_wait(&(inst->dataMem->dataMemReadMutex), &(inst->clk->clockMutex));
                 pthread_cond_wait(&(inst->dataMem->dataMemFinishMutex), &(inst->clk->clockMutex));
                vector[i] = inst->dataMem->data;
            }
            inst->vecRegs->value = vector;
            inst->vecRegs->read = 0;
            inst->vecRegs->index = inst->ctrl->resultReg;
            pthread_cond_signal(&(inst->vecRegs->vectorRegisterCondMutex));
            pthread_cond_wait(&(inst->vecRegs->vectorRegisterWriteMutex), &(inst->clk->clockMutex));
        }
        else if (inst->ctrl->stFlag)
        {
            inst->dataMem->write = 1;
            for (int i = 0; i < 8; i++)
            { 
                inst->dataMem->index = (inst->ctrl->scaDataB) + i;
                inst->dataMem->data = inst->ctrl->vector[i];
                pthread_cond_signal(&(inst->dataMem->dataMemCondMutex));
                // pthread_cond_wait(&(inst->dataMem->dataMemWriteMutex), &(inst->clk->clockMutex));
                 pthread_cond_wait(&(inst->dataMem->dataMemFinishMutex), &(inst->clk->clockMutex));
                
            }
        }
        else if (inst->ctrl->scaMovFlag)
        {
            inst->scaRegs->index = inst->ctrl->scaIndex;
            inst->scaRegs->value = inst->ctrl->scaDataB;
            inst->scaRegs->read = 0;
            pthread_cond_signal(&(inst->scaRegs->scalarRegisterCondMutex));
            pthread_cond_wait(&(inst->scaRegs->scalarRegisterWriteMutex), &(inst->clk->clockMutex));
        }
        else
        {
            inst->resultReg = inst->exe->resultReg;
            inst->vecRegs->index = inst->resultReg;
            inst->vecRegs->value = inst->exe->result;
            inst->vecRegs->read = 0;
            pthread_cond_signal(&(inst->vecRegs->vectorRegisterCondMutex));
            pthread_cond_wait(&(inst->vecRegs->vectorRegisterWriteMutex), &(inst->clk->clockMutex));
        }
        pthread_cond_signal(&(inst->ctrl->controlCondMutex));
        pthread_mutex_unlock(&(inst->clk->clockMutex));
    }
}