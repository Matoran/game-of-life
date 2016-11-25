#ifndef THREAD_H
#define THREAD_H

#include <semaphore.h>
#include <stdbool.h>

typedef struct paramsThreadsSt{
    uint numberThreads;
    uint idThread;
    pthread_barrier_t *workerDisplayBarrier;
    bool **oldState, **actualState;
    uint width, height;
    bool *end;
}paramsThreadsSt;

typedef struct paramsDisplaySt{
    bool **state;
    uint width, height;
    bool *end;
    pthread_barrier_t *workerDisplayBarrier;
    uint numberThreads;
}paramsDisplaySt;
void printTable(uint width, uint height, bool **oldState);
extern void createThreads(uint numberThreads, uint width, uint height, bool **oldState);
extern void *worker(void *paramsThreads);
extern void *display(void *paramsThread);

#endif
