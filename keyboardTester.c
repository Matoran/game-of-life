#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "keyboard.h"
#include "gfx.h"

int main(int argc, char const *argv[]) {
    struct gfx_context_t *ctxt = gfx_create("Example", 1000, 500);
    if (!ctxt) {
        fprintf(stderr, "Graphic mode initialization failed!\n");
        return EXIT_FAILURE;
    }
    bool end = false;
    printf("%d", end);
    keyboard(&end);
    printf("%d", end);
    return EXIT_SUCCESS;
}