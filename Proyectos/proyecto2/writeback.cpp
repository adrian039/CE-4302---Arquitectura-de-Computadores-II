#include "writeback.h"

Writeback::Writeback(Clock *clk_, Control *ctrl_, Execution *exe_, VectorRegisters *vecRegs_, ScalarRegisters *scaRegs_, DataMem *dataMem_)
{
    clk = clk_;
    this->ctrl=ctrl_;
    this->exe = exe_;
    this->vecRegs = vecRegs_;
    this->scaRegs = scaRegs_;
    this->dataMem = dataMem_;
    pthread_create(&threadWriteback, 0, &Writeback::start, (void *)this);
    pthread_join(threadWriteback, NULL);
}

void *Writeback::start(void *ptr)
{
    Writeback *inst = (Writeback *)ptr;
    while(1){
        pthread_mutex_lock(&(inst->clk->clockMutex));
        pthread_cond_wait(&(inst->clk->clockWritebackCondMutex), &(inst->clk->clockMutex));
        if(inst->ctrl->lsldFlag){
            // TODO
        }else{
            inst->resultReg=inst->exe->resultReg;
            inst->vecRegs->index=inst->resultReg;
            inst->vecRegs->value=inst->exe->result;
            inst->vecRegs->read=0;
            pthread_cond_signal(&(inst->vecRegs->vectorRegisterCondMutex));
        }
        pthread_mutex_unlock(&(inst->clk->clockMutex));
    }
}