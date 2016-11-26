//
// Created by matoran on 11/26/16.
//

#include "worker.h"

int neighbour(bool **oldState, int line, int column) {
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

/*
 *   Task of a single thread
 *
 *   paramsThread: struct which contain all information to perform the task
 *
 */
void *worker(void *paramsWorker) {
    paramsWorkerSt *params = (paramsWorkerSt *) paramsWorker;

    int nbNeighbour;
    int jump = params->idThread;
    int size = (params->height - 2) * (params->width - 2);
    int line, column;

    while (!*params->quit) {
        line = jump / (params->width - 2) + 1;
        column = jump % (params->width - 2) + 1;

        nbNeighbour = neighbour(params->oldState, line, column);

        if (params->oldState[line][column]) {
            if (nbNeighbour < 2) {
                params->actualState[line][column] = false;
            }
            if (nbNeighbour == 2 || nbNeighbour == 3) {
                params->actualState[line][column] = true;
            }
            if (nbNeighbour > 3) {
                params->actualState[line][column] = false;
            }
        } else {
            params->actualState[line][column] = (nbNeighbour == 3);
        }

        jump += params->numberThreads;
        if (jump >= size) {
            jump = params->idThread;
            //wait all workers with one workersDisplayBarrier
            pthread_barrier_wait(params->workersDisplayBarrier);
            //attendre l'affichage
            //ZONE CRITIQUE
            while (jump < size) {
                line = jump / (params->width - 2) + 1;
                column = jump % (params->width - 2) + 1;
                jump += params->numberThreads;
                params->oldState[line][column] = params->actualState[line][column];
            }
            jump = params->idThread;
            //FIN ZONE CRITIQUE
            if (*params->end)
                *params->quit = *params->end;
            pthread_barrier_wait(params->workersDisplayBarrier);
            //attendre tous les travailleurs
        }
    }
    return NULL;
}