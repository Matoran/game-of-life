cmake_minimum_required(VERSION 3.6)
project(game_of_life)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu99 -lrt -lpthread -lSDL2")

set(SOURCE_FILES
    main.c
    thread.c
    thread.h keyboard.c keyboard.h keyboardTester.c)

add_executable(game_of_life ${SOURCE_FILES})

set(SOURCE_FILES
        keyboard.c keyboard.h keyboardTester.c)

add_executable(keyboardTester ${SOURCE_FILES})