#include "execution.h"

Execution::Execution(Clock *clk_, Control *control_, Alu *alu1_, Alu *alu2_, Alu *alu3_, Alu *alu4_)
{
    clk = clk_;
    this->ctrl = control_;
    this->alu1 = alu1_;
    this->alu2 = alu2_;
    this->alu3 = alu3_;
    this->alu4 = alu4_;
    pthread_create(&threadExecution, 0, &Execution::start, (void *)this);
    pthread_detach(threadExecution);
}

void *Execution::start(void *ptr)
{
    Execution *inst = (Execution *)ptr;
    while (1)
    {
        pthread_mutex_lock(&(inst->clk->clockMutex));
        pthread_cond_wait(&(inst->ctrl->controlExecutionCondMutex), &(inst->clk->clockMutex));
        inst->aluControl = inst->ctrl->aluSelect;
        inst->alu1->aluControl=inst->aluControl;
        inst->alu2->aluControl=inst->aluControl;
        inst->alu3->aluControl=inst->aluControl;
        inst->alu4->aluControl=inst->aluControl;
        if (inst->ctrl->vectorFlag)
        {
            inst->vectDataA = inst->ctrl->vectDataA;
            inst->vectDataB = inst->ctrl->vectDataB;
            for (int i = 0; i < 2; i++)
            {
                inst->dataA1 = inst->vectDataA[0 + (i * 4)];
                inst->dataA2 = inst->vectDataA[1 + (i * 4)];
                inst->dataA3 = inst->vectDataA[2 + (i * 4)];
                inst->dataA4 = inst->vectDataA[3 + (i * 4)];
                inst->dataB1 = inst->vectDataB[0 + (i * 4)];
                inst->dataB2 = inst->vectDataB[1 + (i * 4)];
                inst->dataB3 = inst->vectDataB[2 + (i * 4)];
                inst->dataB4 = inst->vectDataB[3 + (i * 4)];
                inst->alu1->dataA = inst->dataA1;
                inst->alu1->dataB = inst->dataB1;
                inst->alu2->dataA = inst->dataA2;
                inst->alu2->dataB = inst->dataB2;
                inst->alu3->dataA = inst->dataA3;
                inst->alu3->dataB = inst->dataB3;
                inst->alu4->dataA = inst->dataA4;
                inst->alu4->dataB = inst->dataB4;
                pthread_cond_broadcast(&(inst->clk->clockAluCondMutex));
                pthread_cond_wait(&(inst->alu1->aluResultCondMutex), &(inst->clk->clockMutex));
                sleep(0.5);
                inst->result[0 + (i * 4)] = inst->alu1->result;
                inst->result[1 + (i * 4)] = inst->alu2->result;
                inst->result[2 + (i * 4)] = inst->alu3->result;
                inst->result[3 + (i * 4)] = inst->alu4->result;
            }
        }
        else // sacalar register values and inmediates
        {
        }
        pthread_cond_signal(&(inst->clk->clockWritebackCondMutex));
        pthread_mutex_unlock(&(inst->clk->clockMutex));
    }
}