cmake_minimum_required(VERSION 3.16)
project(cubebot C)

set(CMAKE_C_STANDARD 11)

add_executable(cubebot solver/main.c
        solver/cube.h
        solver/cube.c
        solver/coordinates.c
        solver/coordinates.h
        solver/movetable.c
        solver/movetable.h
        solver/tests.c
        solver/tests.h
        solver/pruning.c
        solver/pruning.h
        solver/solver.c
        solver/solver.h
        packet/packet.h
        solver/uart.c
        solver/uart.h
        packet/packet.h
        packet/packet.c
)
