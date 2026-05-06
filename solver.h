//
// Created by andre on 2026-05-06.
//

#ifndef CUBEBOT_SOLVER_H
#define CUBEBOT_SOLVER_H
#include "cube.h"

typedef struct {
    int twist;
    int flip;
    int slice;
    int cornPerm;
    int sliceSorted;
} coord_t;

coord_t getCoords(const cube_t *C);

int phase1(coord_t coords, int depth, int maxDepth, int lastMove, move_t *solution);
int phase2(coord_t coords, int depth, int maxDepth, int lastMove, move_t *solution);
int solve(const cube_t *c, move_t  *solution);

#endif //CUBEBOT_SOLVER_H
