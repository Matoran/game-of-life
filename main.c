/*
 * Authors: LOPES Marco, ISELI Cyril and RINGOT Gaëtan
 * Purpose: Game Of Life.
 * Language:  C
 * Date : 23 november 2016
 */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "gfx.h"
#include "thread.h"

/*
 *   Check all syntax Errors
 // *
 *   argc: argument counter
 *   argv: table of arguments
 *
 *   returns: number of errors.
 */
int checkSyntaxError(int argc, int width, int height, int seed, double probability, int freq, int workers) {
    int syntaxError = 0;

    if (argc < 7) {
        printf("Usage: ./gameoflife <width> <height> <seed> <p> <freq> <#workers>\n");
        printf("Example: gameoflife 240 135 0 0.75 30 8\n");
        return syntaxError++;
    }

    if ((width < 4) || (height < 4)) {
        syntaxError++;
        printf("Usage for param <width> and <height> : need to be >= 4\n");
    }

    if (seed < 0) {
        syntaxError++;
        printf("Usage for param <seed> : need to be > 0\n");
    }
    if ((probability < 0.0) || (probability > 1.0)) {
        syntaxError++;
        printf("Usage for param <p> : need to be between 0 and 1\n");
    }

    if (freq <= 0) {
        syntaxError++;
        printf("Usage for param <freq> : need to be between > 0\n");
    }

    if (workers < 1) {
        syntaxError++;
        printf("Usage for param <#workers> : need to be between >= 1\n");
    }

    return syntaxError;
}

/*
 *   Call the function calc executed time
 *
 *   argc: argument counter
 *   argv: table of arguments
 *
 *   returns: EXIT_FAILURE or EXIT_SUCCESS
 */
int main(int argc, char const *argv[]) {
    struct timespec start, finish;
    clock_gettime(CLOCK_REALTIME, &start);

    int width = atoi(argv[1]);
    int height = atoi(argv[2]);
    int seed = atoi(argv[3]);
    double probability = atof(argv[4]);
    int freq = atoi(argv[5]);
    int workers = atoi(argv[6]);

    int errors = checkSyntaxError(argc, width, height, seed, probability, freq, workers);
    if (errors > 0) {
        printf("Total errors : %s\n", errors);
        return EXIT_FAILURE;
    }
    srand(seed);
    bool state[width][height];
    for (int line = 0; line < width; ++line) {
        for (int column = 0; column < height; ++column) {
            float random = (float)rand()/(float)(RAND_MAX);
            if (random < probability) {
                state[line][column] = true;
            } else {
                state[line][column] = false;
            }
        }
    }
    createThreads(workers, width, height, state);
    clock_gettime(CLOCK_REALTIME, &finish);
    double elapsed = finish.tv_sec - start.tv_sec;
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
    printf("Executed time: %f s\n", elapsed);
    return EXIT_SUCCESS;
}


