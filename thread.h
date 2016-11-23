#ifndef THREAD_H
#define THREAD_H

#include <semaphore.h>
#include <stdbool.h>

typedef struct paramsThreadsSt{
    int numberThreads;
    int idThread;
    sem_t *barrier;
    bool **oldState, **actualState;
    int width, height;
    bool *end;
}paramsThreadsSt;

extern void createThreads(int numberThreads, int width, int height, bool **oldState);
void *thread(void *paramsThreads);

#endif
