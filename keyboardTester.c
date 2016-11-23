#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "keyboard.h"

int main(int argc, char const *argv[]) {
    bool end = false;
    printf("%d", end);
    run(&end);
    printf("%d", end);
    return EXIT_SUCCESS;
}