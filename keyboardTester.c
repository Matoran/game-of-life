#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "keyboard.h"
#include "gfx.h"

int main() {
    struct gfx_context_t *ctxt = gfx_create("Example", 2, 2);
    if (!ctxt) {
        fprintf(stderr, "Graphic mode initialization failed!\n");
        return EXIT_FAILURE;
    }
    gfx_putpixel(ctxt, 0, 0, COLOR_RED);
    gfx_present(ctxt);
    bool end = false;
    printf("%d", end);
    keyboard(&end);
    printf("%d", end);
    gfx_destroy(ctxt);
    return EXIT_SUCCESS;
}