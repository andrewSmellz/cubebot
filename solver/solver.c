//
// Created by andre on 2026-05-06.
//

#include "solver.h"
#include "coordinates.h"
#include "pruning.h"

coord_t getCoords(const cube_t *c) {
    coord_t coords;
    coords.twist       = cornerOrientationCoordinate(c);
    coords.flip        = edgeOrientationCoordinate(c);
    coords.slice       = udSliceCoordinate(c);
    coords.cornPerm    = cornerPermutationCoordinate(c);
    coords.sliceSorted = udSliceCoordinate2(c);
    coords.edge8Perm   = edge8PermutationCoordinate(c);
    return coords;
}

static int max(int a, int b) {return a > b ? a : b;}

int phase2(coord_t coords, int depth, int maxDepth, int lastFace, move_t *solution) {
    int slicePerm = coords.sliceSorted % 24;

    if (coords.cornPerm == 0 && slicePerm == 0 && coords.edge8Perm == 0) {
        solution[maxDepth - depth] = (move_t)-1;
        return 1;
    }

    if (depth == 0) return 0;

    int h1 = cornPermSlicePrune[coords.cornPerm][slicePerm];
    int h2 = edge8PermSlicePrune[coords.edge8Perm][slicePerm];
    if (max(h1, h2) > depth) return 0;

    static const int p2moves[10] = {0,1,2, 4, 7, 9,10,11, 13, 16};
    for (int mi = 0; mi < 10; mi++) {
        int m = p2moves[mi];
        int face = m / 3;
        if (face == lastFace) continue;
        if (face / 3 == lastFace / 3 && face > lastFace) continue;

        coord_t next;
        next.cornPerm    = cornPermMove[coords.cornPerm][m];
        next.sliceSorted = udSliceSortedMove[coords.sliceSorted][m];
        next.edge8Perm   = edge8PermMove[coords.edge8Perm][m];

        solution[maxDepth - depth] = (move_t)m;
        if (phase2(next, depth - 1, maxDepth, face, solution)) return 1;
    }
    return 0;
}

int phase1(coord_t coords, int depth, int maxDepth, int lastFace, move_t *solution) {
    int h = max(sliceTwistPrune[coords.slice][coords.twist],
                sliceFlipPrune[coords.slice][coords.flip]);
    if (h > depth) return 0;

    if (coords.twist == 0 && coords.flip == 0 && coords.slice == 425) {
        /* Phase 1 solved: slice edges are in their home band (positions 4-7).
         * edge8Perm cannot be tracked reliably through phase1 via move tables
         * (those tables assume slice edges stay in the band, which phase1 moves
         * can violate). Recompute it from the actual cube state by replaying
         * the phase1 moves found so far. */
        int phase1Moves = maxDepth - depth;
        cube_t tmp = coords.root;
        for (int i = 0; i < phase1Moves; i++)
            cubeApplyMove(&tmp, solution[i]);

        coord_t p2coords;
        p2coords.cornPerm    = coords.cornPerm;
        p2coords.sliceSorted = coords.sliceSorted;
        p2coords.edge8Perm   = edge8PermutationCoordinate(&tmp);

        for (int d = 0; d <= 15; d++) {
            if (phase2(p2coords, d, d, -1, solution + phase1Moves))
                return 1;
        }
        return 0;
    }

    if (depth == 0) return 0;

    for (int m = 0; m < 18; m++) {
        int face = m / 3;
        if (face == lastFace) continue;
        if (face / 3 == lastFace / 3 && face > lastFace) continue;

        coord_t nextCoords;
        nextCoords.root        = coords.root;  // carry original cube for replay
        nextCoords.twist       = twistMove[coords.twist][m];
        nextCoords.flip        = flipMove[coords.flip][m];
        nextCoords.slice       = udSliceMove[coords.slice][m];
        nextCoords.cornPerm    = cornPermMove[coords.cornPerm][m];
        nextCoords.sliceSorted = udSliceSortedMove[coords.sliceSorted][m];
        nextCoords.edge8Perm   = 0; // unused during phase1

        solution[maxDepth - depth] = (move_t)m;
        if (phase1(nextCoords, depth - 1, maxDepth, face, solution))
            return 1;
    }
    return 0;
}

int solve(const cube_t *c, move_t *solution) {
    coord_t coords = getCoords(c);
    coords.root = *c;  // store original cube for edge8Perm recomputation at phase boundary
    for (int maxDepth = 0; maxDepth <= 20; maxDepth++) {
        if (phase1(coords, maxDepth, maxDepth, -1, solution))
            return 1;
    }
    return 0;
}