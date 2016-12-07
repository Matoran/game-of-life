#ifndef GAME_OF_LIFE_KEYBOARD_H
#define GAME_OF_LIFE_KEYBOARD_H

#include <stdbool.h>
#include <pthread.h>

typedef struct paramsKeyboardSt {
    bool *end;
    pthread_barrier_t *displayInitialised;
} paramsKeyboardSt;

extern void *keyboard(void *paramKeyboard);

#endif //GAME_OF_LIFE_KEYBOARD_H
