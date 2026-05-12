//
// Created by andre on 2026-04-30.
//

#ifndef CUBEBOT_MOVETABLE_H
#define CUBEBOT_MOVETABLE_H
#include "cube.h"
#include "coordinates.h"

extern int twistMove[2187][18];
extern int flipMove[2048][18];
extern int udSliceMove[495][18];
extern int cornPermMove[40320][18];
extern int udSliceSortedMove[11880][18];
extern int edge8PermMove[40320][18];

void createMoveTables(void);


#endif //CUBEBOT_MOVETABLE_H
