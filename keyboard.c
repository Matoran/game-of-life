//
// Created by matoran on 11/23/16.
//

#include "keyboard.h"
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>
#define FREQUENCE 50

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

void *keyboard(void *param){
    bool *end = (bool*)param;
    struct timespec start, finish;
    double microSecondToWait = 1000000.0/FREQUENCE;
    printf("%lf\n", microSecondToWait);
    while (!*end) {
        clock_gettime(CLOCK_REALTIME, &start);
        if(keypress() == SDLK_ESCAPE)
            *end = true;
        clock_gettime(CLOCK_REALTIME, &finish);
        double elapsed = (finish.tv_nsec - start.tv_nsec) / 1000.0;
        printf("%lf\n", elapsed);
        usleep(microSecondToWait-elapsed);
    }
}
