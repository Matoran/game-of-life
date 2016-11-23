cmake_minimum_required(VERSION 3.6)
project(game_of_life)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu99 -lrt -lpthread -lSDL2")

set(SOURCE_FILES
    main.c gfx.c gfx.h keyboard.c keyboard.h thread.c thread.h)

add_executable(game_of_life ${SOURCE_FILES})

set(SOURCE_FILES
        keyboard.c keyboard.h keyboardTester.c gfx.c gfx.h)

add_executable(keyboardTester ${SOURCE_FILES})