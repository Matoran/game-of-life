cmake_minimum_required(VERSION 3.6)
project(game_of_life)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    main.c
    makefile
    thread.c
    thread.h)

add_executable(game_of_life ${SOURCE_FILES})