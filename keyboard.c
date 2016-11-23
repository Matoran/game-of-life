//
// Created by matoran on 11/23/16.
//

#include "keyboard.h"
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>

/// If a key was pressed, returns its key code (non blocking call).
/// List of key codes: https://wiki.libsdl.org/SDL_Keycode
/// @return the key that was pressed or 0 if none was pressed.
static SDL_Keycode keypress() {
    SDL_Event event;
    if (SDL_PollEvent(&event)) {
        if (event.type == SDL_KEYDOWN)
            return event.key.keysym.sym;
    }
    return 0;
}

void *run(void *param){
    bool *end = (bool*)param;
    struct timespec start, finish;


    while (!*end) {
        clock_gettime(CLOCK_MONOTONIC, &start);
        if(keypress() == SDLK_ESCAPE)
            *end = true;
        clock_gettime(CLOCK_MONOTONIC, &finish);
        double elapsed = finish.tv_sec - start.tv_sec;
        elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
        usleep(1000000.0-elapsed);
    }
    *end = true;
}
