/*
 * Authors: LOPES Marco, ISELI Cyril and RINGOT Gaëtan
 * Purpose: Game Of Life.
 * Language:  C
 * Date : 23 november 2016
 */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "thread.h"
#include "keyboard.h"

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
    clock_gettime(CLOCK_MONOTONIC, &start);

    errors = checkSyntaxError()
    if (errors > 0) {
        printf("Total errors : %s\n", errors);
        return EXIT_FAILURE;
    }

     double elapsed = finish.tv_sec - start.tv_sec;
     elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
     printf("Executed time: %f s\n", elapsed);
     return EXIT_SUCCESS;

}

/*
 *   Check all syntax Errors
 *
 *   returns: number of errors.
 */
int checkSyntaxError(){
    int syntaxError = 0;

    if (argc < 7) {
        printf("Usage: ./gameoflife <width> <height> <seed> <p> <freq> <#workers>\n");
        printf("Example: gameoflife 240 135 0 0.75 30 8\n");`
        return syntaxError++;`
    }

    if ((argv[1] < 4) || (argv[2]< 4)) {
        syntaxError ++;
        printf("Usage for param <width> and <height> : need to be >= 4\n");
    }

    if ((argv[4] < 0) || (argv[4] > 1)) {
        syntaxError ++;
        printf("Usage for param <p> : need to be between 0 and 1\n");
    }

    if (argv[5] <= 0) {
        syntaxError ++;
        printf("Usage for param <freq> : need to be between > 0\n");
    }

    if (argv[6] < 1) {
        syntaxError ++;
        printf("Usage for param <#workers> : need to be between >= 1\n");
    }

    return syntaxError;
}
