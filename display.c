//
// Created by matoran on 11/26/16.
//

#include "display.h"
#include "gfx.h"
#include <unistd.h>

void *display(void *paramsDisplay) {
    paramsDisplaySt *params = (paramsDisplaySt *) paramsDisplay;

    struct gfx_context_t *ctxt = gfx_create("Example", params->width, params->height);
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
                if (params->state[line][column]) {
                    gfx_putpixel(ctxt, column, line, COLOR_GREEN);
                }

            }
        }
        gfx_present(ctxt);
        pthread_barrier_wait(params->workerDisplayBarrier);
        if (*params->end)
            *params->quit = *params->end;
        pthread_barrier_wait(params->workerDisplayBarrier);

        clock_gettime(CLOCK_REALTIME, &finish);
        double elapsed = (finish.tv_nsec - start.tv_nsec) / 1000.0;
        if (microSecondToWait - elapsed > 0)
            usleep(microSecondToWait - elapsed);
    }

    gfx_destroy(ctxt);
    return NULL;
}
