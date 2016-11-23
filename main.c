/*
 * Authors: LOPES Marco, ISELI Cyril and RINGOT Gaëtan
 * Purpose: Password cracker.
 * Language:  C
 * Date : 23 november 2016
 */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "thread.h"

/*
 *   Call the function create threads and calc executed time
 *
 *   argc: argument counter
 *   argv: table of arguments
 *
 *   returns: EXIT_FAILURE or EXIT_SUCCESS
 */
int main(int argc, char const *argv[]) {
    struct timespec start, finish;
    clock_gettime(CLOCK_MONOTONIC, &start);

    
    double elapsed = finish.tv_sec - start.tv_sec;
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
    printf("Executed time: %f s\n", elapsed);
    return EXIT_SUCCESS;
}
