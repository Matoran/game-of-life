#ifndef THREAD_H
#define THREAD_H

#include <semaphore.h>
#include <stdbool.h>

typedef struct paramsThreadsSt{
    uint numberThreads;
    uint idThread;
    sem_t *barrier;
    bool **oldState, **actualState;
    uint width, height;
    bool *end;
}paramsThreadsSt;

typedef struct paramsDisplaySt{
    bool **state;
    uint width, height;
    bool *end;
    sem_t *barrier;
    uint numberThreads;
}paramsDisplaySt;

extern void createThreads(uint numberThreads, uint width, uint height, bool **oldState);
extern void *worker(void *paramsThreads);
extern void *display(void *paramsThread);

#endif
