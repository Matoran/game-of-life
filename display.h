#ifndef GAME_OF_LIFE_DISPLAY_H
#define GAME_OF_LIFE_DISPLAY_H

#include "pthread.h"
#include "stdbool.h"

typedef unsigned int uint;

typedef struct paramsDisplaySt {
    bool ***oldState, ***actualState;
    uint width, height;
    uint frequency;
    bool *end, *quit;
    pthread_barrier_t *workerDisplayBarrier;
} paramsDisplaySt;

extern void *display(void *paramsDisplay);

#endif //GAME_OF_LIFE_DISPLAY_H
