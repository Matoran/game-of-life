#ifndef GAME_OF_LIFE_WORKER_H
#define GAME_OF_LIFE_WORKER_H

#include <pthread.h>
#include <stdbool.h>

typedef unsigned int  uint;

typedef struct paramsWorkerSt{
    uint numberThreads;
    uint idThread;
    pthread_barrier_t *workersDisplayBarrier;
    bool **oldState, **actualState;
    uint width, height;
    bool *quit;
}paramsWorkerSt;

extern void *worker(void *paramsWorker);

#endif //GAME_OF_LIFE_WORKER_H
