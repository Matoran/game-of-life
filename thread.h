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

typedef struct paramsDisplaySt{
    bool **state;
    int width, height;
    bool *end;
    sem_t *barrier;
    int numberThreads;
}paramsDisplaySt;

extern void createThreads(int numberThreads, int width, int height, bool **oldState);
void *worker(void *paramsThreads);
void *display(void *paramsThread);

#endif
