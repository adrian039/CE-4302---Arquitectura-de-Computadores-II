
#include "clock.h"

Clock::Clock()
{
    int selector = 2;
    while (selector != 1 && selector != 0)
    {
        std::cout << "Type 1 for use automatic clock or 0 for manual clock: ";
        std::cin >> selector;
    }
    this->clockControl = selector;
    pthread_create(&clockThread, 0, &Clock::startClock, (void *)this);
    pthread_create(&controlThread, 0, &Clock::clockController, (void *)this);
    pthread_join(clockThread, NULL);
    pthread_join(controlThread, NULL);
}

void *Clock::startClock(void *ptr)
{
    Clock *inst = (Clock *)ptr;
    while (1)
    {
        pthread_mutex_lock(&(inst->clockMutex));
        pthread_cond_wait(&(inst->clockCondMutex), &(inst->clockMutex));
        inst->counter++;
        std::cout << "******* Ciclo: " << std::to_string(inst->counter) << " *********" << std::endl;
        pthread_mutex_unlock(&(inst->clockMutex));
    }
}

void *Clock::clockController(void *ptr)
{
    Clock *inst = (Clock *)ptr;
    pthread_mutex_lock(&(inst->clockMutex));
    while (1)
    {
        if (inst->clockControl)
        {
            pthread_cond_signal(&(inst->clockCondMutex));
            pthread_mutex_unlock(&(inst->clockMutex));
            sleep(0.1);
        }
        else
        {
            int val = 0;
            std::cout << "Type 1 and Enter for next cycle: ";
            std::cin >> val;
            std::cout << "\n";
            if (val)
            {
                pthread_cond_signal(&(inst->clockCondMutex));
                pthread_mutex_unlock(&(inst->clockMutex));
                sleep(0.1);
            }
        }
    }
}