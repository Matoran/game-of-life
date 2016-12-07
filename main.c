/**
 * @authors: LOPES Marco, ISELI Cyril and RINGOT Gaëtan
 * Purpose: Game Of Life
 * Language:  C
 * Date : 23 november 2016
 */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "gfx.h"
#include "thread.h"

/**
 * Check all syntax Errors
 *
 * @param width: window width
 * @param height: window height
 * @param probability: probability of live
 * @param freq: image per second
 * @param workers: number of workers
 * @return number of errors
 */
int checkSyntaxError(uint width, uint height, double probability, uint freq, uint workers) {
    int syntaxError = 0;
    if ((width < 4) || (height < 4)) {
        syntaxError++;
        printf("Usage for param <width> and <height> : need to be >= 4\n");
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

/**
 * Program entry, calc execution time, check params and generate first state
 *
 * @param argc number of arguments
 * @param argv table of arguments
 * @return EXIT_FAILURE or EXIT_SUCCESS
 */
int main(int argc, char const *argv[]) {
    if ((argc < 7) || (argc > 7)) {
        printf("Usage: ./gameoflife <width> <height> <seed> <p> <freq> <#workers>\n");
        printf("Example: gameoflife 240 135 0 0.75 30 8\n");
        return EXIT_FAILURE;
    }

    struct timespec start, finish;
    clock_gettime(CLOCK_REALTIME, &start);

    uint width = atoi(argv[1]);
    uint height = atoi(argv[2]);
    uint seed = atoi(argv[3]);
    double probability = atof(argv[4]);
    uint frequency = atoi(argv[5]);
    uint workers = atoi(argv[6]);

    int errors = checkSyntaxError(width, height, probability, frequency, workers);
    if (errors > 0) {
        printf("Total errors : %d\n", errors);
        return EXIT_FAILURE;
    }
    srand(seed);
    bool **oldState = malloc(sizeof(bool *) * height);
    for (uint line = 0; line < height; ++line) {
        oldState[line] = malloc(sizeof(bool) * width);
        for (uint column = 0; column < width; ++column) {
            float random = (float) rand() / (float) (RAND_MAX);
            if (line == 0 || line == height - 1 || column == 0 || column == width - 1) {
                oldState[line][column] = false;
            } else if (random < probability) {
                oldState[line][column] = true;
            } else {
                oldState[line][column] = false;
            }
        }
    }

    createThreads(workers, width, height, &oldState, frequency);
    clock_gettime(CLOCK_REALTIME, &finish);
    double elapsed = finish.tv_sec - start.tv_sec;
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
    printf("Executed time: %f s\n", elapsed);
    for (uint line = 0; line < height; ++line) {
        free(oldState[line]);
    }
    free(oldState);
    return EXIT_SUCCESS;
}
