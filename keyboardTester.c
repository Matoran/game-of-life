/**
 * @authors LOPES Marco, ISELI Cyril and RINGOT Gaëtan
 * Purpose: Test keyboard manager
 * Language:  C
 * Date : november 2016
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>
#include "keyboard.h"
#include "gfx.h"

/**
 * Create SDL context and test keyboard manager
 *
 * @return EXIT_FAILURE or EXIT_SUCCESS
 */
int main() {
    struct gfx_context_t *ctxt = gfx_create("Example", 2, 2);
    if (!ctxt) {
        fprintf(stderr, "Graphic mode initialization failed!\n");
        return EXIT_FAILURE;
    }
    gfx_putpixel(ctxt, 0, 0, COLOR_RED);
    gfx_present(ctxt);
    bool end = false;
    pthread_barrier_t displayInitialised;
    pthread_barrier_init(&displayInitialised, NULL, 1);
    paramsKeyboardSt paramsKeyboard;
    paramsKeyboard.end = &end;
    paramsKeyboard.displayInitialised = &displayInitialised;
    printf("%d", end);
    keyboard(&paramsKeyboard);
    printf("%d", end);
    gfx_destroy(ctxt);
    return EXIT_SUCCESS;
}