/*
 * Authors: LOPES Marco, ISELI Cyril and RINGOT Gaëtan
 * Purpose: Management of worker
 * Language:  C
 * Date : november 2016
 */

#include "worker.h"

/**
 * Calc number of neighbours
 *
 * @param oldState: array of cases
 * @param line: case line
 * @param column: case column
 * @return number of neighbours
 */
int neighbour(bool **oldState, uint line, uint column) {
    int nbALive = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i || j) {
                if (oldState[line + i][column + j]) {
                    nbALive++;
                }
            }
        }
    }
    return nbALive;
}

/**
 * Calc the next state with the rules of "Games of Life"
 *
 * @param oldState: array of cases
 * @param line: case line
 * @param column: case column
 * @return new state
 */

bool nextState(bool **oldState, uint line, uint column) {
    int nbNeighbour = neighbour(oldState, line, column);
    if (oldState[line][column]) {
        if (nbNeighbour < 2) {
            return false;
        } else if (nbNeighbour == 2 || nbNeighbour == 3) {
            return true;
        } else {
            return false;
        }
    } else {
        return (nbNeighbour == 3);
    }
}

/**
 * Task of a single thread
 *
 * @param paramsWorker: struct which contain all information to perform the task
 * @return NULL
 */
void *worker(void *paramsWorker) {
    paramsWorkerSt *params = (paramsWorkerSt *) paramsWorker;
    uint jump = params->idThread;
    uint size = (params->height - 2) * (params->width - 2);
    uint line, column;

    while (!*params->quit) {
        line = jump / (params->width - 2) + 1;
        column = jump % (params->width - 2) + 1;

        (*params->actualState)[line][column] = nextState(*params->oldState, line, column);

        jump += params->numberThreads;
        if (jump >= size) {
            jump = params->idThread;
            pthread_barrier_wait(params->workersDisplayBarrier);
            pthread_barrier_wait(params->workersDisplayBarrier);
        }
    }
    return NULL;
}