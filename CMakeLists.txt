cmake_minimum_required(VERSION 3.6)
project(game_of_life)

<<<<<<< HEAD
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    main.c
    makefile
    thread.c
    thread.h)
=======
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu99 -lrt -lpthread -LSDL2")

set(SOURCE_FILES
    main.c
    thread.c
    thread.h keyboard.c keyboard.h)
>>>>>>> origin/master

add_executable(game_of_life ${SOURCE_FILES})