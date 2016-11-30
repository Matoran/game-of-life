/**
 * @authors: LOPES Marco, ISELI Cyril and RINGOT Gaëtan
 * Purpose: Management of threads
 * Language:  C
 * Date : november 2016
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "worker.h"
#include "display.h"
#include "keyboard.h"

/**
 * Generate a number of threads
 *
 * @param numberWorkers: number max of threads
 * @param width: window width
 * @param height: window height
 * @param oldState: array 2D of booleans
 * @param frequency: image per second
 */
void createThreads(uint numberWorkers, uint width, uint height, bool **oldState, uint frequency) {
    pthread_t threads[numberWorkers + 2];
    paramsWorkerSt paramsThread[numberWorkers];

    pthread_barrier_t barrier;
    pthread_barrier_init(&barrier, NULL, numberWorkers + 1);
    bool end = false, quit = false;

    bool **state = malloc(sizeof(bool *) * height);
    for (uint line = 0; line < height; ++line) {
        state[line] = malloc(sizeof(bool) * width);
    }
    for (uint i = 0; i < numberWorkers; i++) {
        paramsThread[i].idThread = i;
        paramsThread[i].numberThreads = numberWorkers;
        paramsThread[i].workersDisplayBarrier = &barrier;
        paramsThread[i].width = width;
        paramsThread[i].height = height;
        paramsThread[i].oldState = oldState;
        paramsThread[i].actualState = state;
        paramsThread[i].quit = &quit;
        int code = pthread_create(&threads[i], NULL, worker, &paramsThread[i]);
        if (code != 0) {
            fprintf(stderr, "pthread_create failed!\n");
        }
    }
    paramsDisplaySt paramsDisplay;
    paramsDisplay.end = &end;
    paramsDisplay.height = height;
    paramsDisplay.width = width;
    paramsDisplay.oldState = oldState;
    paramsDisplay.actualState = state;
    paramsDisplay.workerDisplayBarrier = &barrier;
    paramsDisplay.quit = &quit;
    paramsDisplay.frequency = frequency;
    int code = pthread_create(&threads[numberWorkers], NULL, display, &paramsDisplay);
    if (code != 0) {
        fprintf(stderr, "pthread_create failed!\n");
    }
    code = pthread_create(&threads[numberWorkers + 1], NULL, keyboard, &end);
    if (code != 0) {
        fprintf(stderr, "pthread_create failed!\n");
    }

    for (uint i = 0; i < numberWorkers + 2; ++i) {
        pthread_join(threads[i], NULL);
    }
    for (uint line = 0; line < height; ++line) {
        free(state[line]);
    }
    free(state);

    pthread_barrier_destroy(&barrier);
}
