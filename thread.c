/*
 * Authors: LOPES Marco, ISELI Cyril and RINGOT Gaëtan
 * Purpose: Management of threads.
 * Language:  C
 * Date : 23 november 2016
 */

#define _GNU_SOURCE

#include <crypt.h>
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "gfx.h"
#include "thread.h"
#include "keyboard.h"
#include <semaphore.h>
#include <stdbool.h>

/*
 *   Generate a number of threads
 *
 *
 *
 */
void createThreads(int numberThreads, int width, int height, bool **oldState) {
    pthread_t threads[numberThreads+2];
    paramsThreadsSt paramsThread[numberThreads];
    sem_t barrier;
    sem_init(&barrier, 0, 0);
    bool end = false;
    for (int i = 0; i < numberThreads; i++) {
        paramsThread[i].idThread = i;
        paramsThread[i].numberThreads = numberThreads;
        paramsThread[i].barrier = &barrier;
        paramsThread[i].width = width;
        paramsThread[i].height = height;
        paramsThread[i].oldState = oldState;
        paramsThread[i].end = &end;
        int code = pthread_create(&threads[i], NULL, worker, &paramsThread[i]);
        if (code != 0) {
            fprintf(stderr, "pthread_create failed!\n");
        }
    }
    paramsDisplaySt paramsDisplay;
    paramsDisplay.end = &end;
    paramsDisplay.height = height;
    paramsDisplay.width = width;
    paramsDisplay.state = oldState;
    paramsDisplay.barrier = &barrier;
    paramsDisplay.numberThreads = numberThreads;
    int code = pthread_create(&threads[numberThreads], NULL, display, &paramsDisplay);
    if (code != 0) {
        fprintf(stderr, "pthread_create failed!\n");
    }
    code = pthread_create(&threads[numberThreads+1], NULL, keyboard, &end);
    if (code != 0) {
        fprintf(stderr, "pthread_create failed!\n");
    }

    for (int i = 0; i < numberThreads+2; ++i) {
        pthread_join(threads[i], NULL);
    }

}


int neighbour(bool **oldState, int line, int column){
    int nbALive = 0;
    for(int i = -1; i <= 1; i++){
        for(int j = -1; j <= 1; j++){
            if(i || j){
                if(oldState[line+i][column+j]){
                    nbALive++;
                }
            }
        }
    }
    return nbALive;
}

/*
 *   Task of a single thread
 *
 *   paramsThread: struct which contain all information to perform the task
 *
 */
void *worker(void *paramsThreads) {
    paramsThreadsSt *params = (paramsThreadsSt *) paramsThreads;

    int nbNeighbour;
    int jump = params->idThread;
    int size = (params->height-2)*(params->width-2);
    int line,column;

    while(!params->end){
        line = jump / (params->width-2) + 1;
        column = jump % (params->height-2) + 1;

        nbNeighbour = neighbour(params->oldState, line, column);

        if(params->oldState[line][column]) {
            if (nbNeighbour < 2) {
                params->actualState[line][column] = false;
            }
            if (nbNeighbour == 2 || nbNeighbour == 3) {
                params->actualState[line][column] = true;
            }
            if (nbNeighbour > 3) {
                params->actualState[line][column] = false;
            }
        }else{
            if(nbNeighbour == 3){
                params->actualState[line][column] = true;
            }
        }

        jump += params->numberThreads;
        if(jump <= size){
            sem_wait(params->barrier);
            jump = params->idThread;
        }
    }
}

void *display(void *paramsDisplay){
    paramsDisplaySt *params = (paramsDisplaySt*)paramsDisplay;

    struct gfx_context_t *ctxt = gfx_create("Example", params->width, params->height);
    if (!ctxt) {
        fprintf(stderr, "Graphic mode initialization failed!\n");
        exit(1);
    }

    while (!*params->end) {
        for (int i = 0; i < params->numberThreads; ++i) {
            sem_wait(params->barrier);
        }

        gfx_clear(ctxt, COLOR_BLACK);
        for (int line = 0; line < params->width; ++line) {
            for (int column = 0; column < params->height; ++column) {
                if(params->state[line][column]){
                    gfx_putpixel(ctxt, line, column, COLOR_GREEN);
                }

            }
        }
        gfx_present(ctxt);
    }

    gfx_destroy(ctxt);
}
