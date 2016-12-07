/**
 * @authors LOPES Marco, ISELI Cyril and RINGOT Gaëtan
 * Purpose: Management of keyboard
 * Language:  C
 * Date : november 2016
 */

#include "keyboard.h"
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <unistd.h>
#define FREQUENCE 50

/**
 * If a key was pressed, returns its key code (non blocking call).
 * List of key codes: https://wiki.libsdl.org/SDL_Keycode
 *
 * @return the key that was pressed or 0 if none was pressed.
 */
static SDL_Keycode keypress() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_KEYDOWN)
            return event.key.keysym.sym;
    }
    return 0;
}

/**
 * End program if the key esc is pressed
 *
 * @param paramsKeyboard: shared bool between all threads
 * @return NULL
 */
void *keyboard(void *paramsKeyboard){
    paramsKeyboardSt *params = (paramsKeyboardSt*)paramsKeyboard;
    struct timespec start, finish;
    double microSecondToWait = 1000000.0/FREQUENCE;
    pthread_barrier_wait(params->displayInitialised);
    while (!*params->end) {
        clock_gettime(CLOCK_REALTIME, &start);
        if(keypress() == SDLK_ESCAPE){
            *params->end = true;
        }
        clock_gettime(CLOCK_REALTIME, &finish);
        double elapsed = (finish.tv_sec-start.tv_sec)*1000000;
        elapsed += (finish.tv_nsec - start.tv_nsec) / 1000.0;
        if(microSecondToWait-elapsed > 0)
            usleep(microSecondToWait-elapsed);
    }
    return NULL;
}
