cmake_minimum_required(VERSION 4.1)
project(cubebot C)

set(CMAKE_C_STANDARD 11)

add_executable(cubebot main.c
        cube.h
        cube.c
        solver.c
        solver.h
        movetable.c
        movetable.h)
