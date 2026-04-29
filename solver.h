//
// Created by andre on 2026-04-28.
//

#ifndef CUBEBOT_SOLVER_H
#define CUBEBOT_SOLVER_H
#include "cube.h"

int cornerOrientationCoordinate(const cube_t *c);
int edgeOrientationCoordinate(const cube_t *c);
int udSliceCoordinate(const cube_t *c);

#endif //CUBEBOT_SOLVER_H
