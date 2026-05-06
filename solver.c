//
// Created by andre on 2026-05-06.
//

#include "solver.h"
#include "coordinates.h"

coord_t getCoords(const cube_t *c) {
    coord_t coords;
    coords.twist       = cornerOrientationCoordinate(c);
    coords.flip        = edgeOrientationCoordinate(c);
    coords.slice       = udSliceCoordinate(c);
    coords.cornPerm    = cornerPermutationCoordinate(c);
    coords.sliceSorted = udSliceCoordinate2(c);
    return coords;
}

int phase1(coord_t coords, int depth, int maxDepth, int lastMove, move_t *solution) {
}