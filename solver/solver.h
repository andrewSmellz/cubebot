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
    int edge8Perm;
    cube_t root;  // original scrambled cube, for replaying phase1 moves at the phase boundary
} coord_t;

coord_t getCoords(const cube_t *C);

static int max(int a, int b);

int phase2(coord_t coords, int depth, int maxDepth, int lastFace, move_t *solution);
int phase1(coord_t coords, int depth, int maxDepth, int lastFace, move_t *solution);

int solve(const cube_t *c, move_t  *solution);

#endif //CUBEBOT_SOLVER_H