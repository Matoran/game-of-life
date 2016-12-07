/**
 * @authors LOPES Marco, ISELI Cyril and RINGOT Gaëtan
 * Purpose: Management of display
 * Language:  C
 * Date : november 2016
 */

#include "display.h"
#include "gfx.h"
#include <unistd.h>

/**
 * Display "Game of Life"
 * @param paramsDisplay: struct which contain all informations to perform the display
 * @return NULL
 */
void *display(void *paramsDisplay) {
    paramsDisplaySt *params = (paramsDisplaySt *) paramsDisplay;

    struct gfx_context_t *ctxt = gfx_create("gofl", params->width, params->height);
    if (!ctxt) {
        fprintf(stderr, "Graphic mode initialization failed!\n");
        exit(1);
    }
    struct timespec start, finish;
    double microSecondToWait = 1000000.0 / params->frequency;

    while (!*params->quit) {
        clock_gettime(CLOCK_REALTIME, &start);

        gfx_clear(ctxt, COLOR_BLACK);
        for (uint line = 0; line < params->height; ++line) {
            for (uint column = 0; column < params->width; ++column) {
                if ((*params->oldState)[line][column]) {
                    gfx_putpixel(ctxt, column, line, COLOR_YELLOW);
                }

            }
        }
        gfx_present(ctxt);
        pthread_barrier_wait(params->workerDisplayBarrier);
        if (*params->end)
            *params->quit = *params->end;
        bool **temp = *params->oldState;
        *params->oldState = *params->actualState;
        *params->actualState = temp;
        pthread_barrier_wait(params->workerDisplayBarrier);

        clock_gettime(CLOCK_REALTIME, &finish);
        double elapsed = (finish.tv_sec - start.tv_sec) * 1000000;
        elapsed += (finish.tv_nsec - start.tv_nsec) / 1000.0;
        if (microSecondToWait - elapsed > 0) {
            usleep(microSecondToWait - elapsed);
        }
    }

    gfx_destroy(ctxt);
    return NULL;
}
