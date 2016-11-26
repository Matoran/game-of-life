#ifndef THREAD_H
#define THREAD_H

#include <stdbool.h>

extern void createThreads(uint numberWorkers, uint width, uint height, bool **oldState, uint frequency);

#endif
