#include "control.h"

Control::Control(Clock *clk_, InstMem *instMem_, VectorRegisters *vectRegs_, ScalarRegisters *scaRegs_, DataMem *datMem_)
{
    clk = clk_;
    this->instMem = instMem_;
    this->vectRegs = vectRegs_;
    this->scaRegs = scaRegs_;
    this->datMem = datMem_;
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
        //  pthread_mutex_lock(&(inst->controlMutex));
        pthread_cond_wait(&(inst->clk->clockControlCondMutex), &(inst->clk->clockMutex));
        
        inst->scaMovFlag = 0;
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
            pthread_cond_wait(&(inst->clk->clockCondMutex), &(inst->clk->clockMutex)); // ***** PIPELINE BEHAVIOR *****//
            std::cout << "DECODE STARTED" << std::endl;
            if (opcode == 0 || opcode == 3 || opcode == 6 || opcode == 9)
            {
                std::cout<<"VADD"<<std::endl;
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
                pthread_cond_signal(&(inst->controlExecutionCondMutex));
            }
            else if (opcode == 2 || opcode == 5 || opcode == 8 || opcode == 11)
            {
                inst->vectorFlag = 0;
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
                inst->scaRegs->index = datB - 16;
                inst->scaRegs->read = 1;
                pthread_cond_signal(&(inst->scaRegs->scalarRegisterCondMutex));
                pthread_cond_wait(&(inst->scaRegs->scalarRegisterReadMutex), &(inst->clk->clockMutex));
                inst->scaRegs->read = 0;
                inst->scaDataB = inst->scaRegs->value;
                switch (opcode)
                {
                case 2:
                    inst->aluSelect = 1;
                    break;
                case 5:
                    inst->aluSelect = 2;
                    break;
                case 8:
                    inst->aluSelect = 3;
                    break;
                case 11:
                    inst->aluSelect = 4;
                    break;
                }
                pthread_cond_signal(&(inst->controlExecutionCondMutex));
            }
            else if (opcode == 1 || opcode == 4 || opcode == 7 || opcode == 12 || opcode == 13 || opcode == 18)
            {
                inst->vectorFlag = 0;
                datA = inst->getData(instruction.substr(10, 5));
                datB = inst->getData(instruction.substr(15, 9));
                datR = inst->getData(instruction.substr(5, 5));
                inst->resultReg = datR;
                inst->vectRegs->index = datA;
                inst->vectRegs->read = 1;
                pthread_cond_signal(&(inst->vectRegs->vectorRegisterCondMutex));
                pthread_cond_wait(&(inst->vectRegs->vectorRegisterReadMutex), &(inst->clk->clockMutex));
                inst->vectRegs->read = 0;
                inst->vectDataA = inst->vectRegs->value;
                inst->scaDataB = datB;
                switch (opcode)
                {
                case 1:
                    inst->aluSelect = 1;
                    break;
                case 4:
                    inst->aluSelect = 2;
                    break;
                case 7:
                    inst->aluSelect = 3;
                    break;
                case 12:
                    //std::cout << "VROTR 1" << std::endl;
                    inst->aluSelect = 5;
                    break;
                case 13:
                    inst->aluSelect = 4;
                    break;
                case 18:
                    //std::cout << "VLROTR 1" << std::endl;
                    inst->aluSelect = 6;
                    break;
                }
                pthread_cond_signal(&(inst->controlExecutionCondMutex));
            }
            else if (opcode == 10 || opcode == 14 || opcode == 15 || opcode == 16 || opcode == 17)
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
                    inst->vectRegs->read = 1;
                    pthread_cond_signal(&(inst->vectRegs->vectorRegisterCondMutex));
                    pthread_cond_wait(&(inst->vectRegs->vectorRegisterReadMutex), &(inst->clk->clockMutex));
                    inst->vectRegs->read = 0;
                    inst->vector = inst->vectRegs->value;
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
                else if (opcode == 16)
                {
                    inst->scaDataB = datA;
                    inst->scaIndex = datR - 16;
                    inst->scaMovFlag = 1;
                    inst->ldFlag = 0;
                    inst->stFlag = 0;
                    pthread_cond_signal(&(inst->clk->clockWritebackCondMutex));
                }
                else if (opcode == 10)
                {
                    //std::cout << "VROT 1" << std::endl;
                    inst->ldFlag = 0;
                    inst->stFlag = 0;
                    inst->scaDataB = datA;
                    inst->aluSelect = 5;
                    inst->vectRegs->read = 1;
                    pthread_cond_signal(&(inst->vectRegs->vectorRegisterCondMutex));
                    pthread_cond_wait(&(inst->vectRegs->vectorRegisterReadMutex), &(inst->clk->clockMutex));
                    inst->vectRegs->read = 0;
                    inst->vectDataA = inst->vectRegs->value;
                    pthread_cond_signal(&(inst->controlExecutionCondMutex));
                }
                else if (opcode == 17)
                {
                    //std::cout << "VLROT 1" << std::endl;
                    inst->ldFlag = 0;
                    inst->stFlag = 0;
                    inst->scaDataB = datA;
                    inst->aluSelect = 6;
                    inst->vectRegs->read = 1;
                    pthread_cond_signal(&(inst->vectRegs->vectorRegisterCondMutex));
                    pthread_cond_wait(&(inst->vectRegs->vectorRegisterReadMutex), &(inst->clk->clockMutex));
                    inst->vectRegs->read = 0;
                    inst->vectDataA = inst->vectRegs->value;
                    pthread_cond_signal(&(inst->controlExecutionCondMutex));
                }
            }
        }
        else
        {
            std::cout << "INSTRUCTIONS EMPTY..." << std::endl;
            std::cout << "WRITING OUT IMAGE..." << std::endl;
            FILE *fpOut;
            fpOut = fopen(outFile, "wb");
            unsigned char *image;
            image = (unsigned char *)malloc(columns * rows);
            for(int i=0; i<(rows*columns); i++){
                // if(i<100){
                //     std::cout<<"PIXEL "<<i<<": "<<inst->datMem->dataMemory[i]<<std::endl;
                // }
                image[i]=(unsigned char)inst->datMem->dataMemory[i];
            }
            if (fpOut == NULL)
            {
                perror("Error couldn't write the image ");
                exit;
            }
            fprintf(fpOut, "P%d\n%d %d\n%d\n", 5, columns, rows, highval);
            fwrite(image, 1, (columns * rows), fpOut);
            free(image);
            std::cout << "PROCESS FINISHED..." << std::endl;
            exit(0);
            // instructions completed!
        }
        inst->pc++;
        // std::cout<<"ESPERO"<<std::endl;
        pthread_cond_wait(&(inst->controlCondMutex), &(inst->clk->clockMutex));
        // std::cout<<"SALI"<<std::endl;
        //  pthread_mutex_unlock(&(inst->controlMutex));
        pthread_mutex_unlock(&(inst->clk->clockMutex));
    }
}