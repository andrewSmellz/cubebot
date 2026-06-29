//
// Created by andre on 2026-05-06.
//

#include "pruning.h"
#include <string.h>

int8_t  sliceTwistPrune[495][2187];
int8_t  sliceFlipPrune[495][2048];
int8_t  cornPermSlicePrune[40320][24];
int8_t edge8PermSlicePrune[40320][24];

static const int phase2Moves[10] = {
    0, 1, 2,   // U1, U2, U'
    4,         // R2
    7,         // F2
    9, 10, 11, // D1, D2, D'
    13,        // L2
    16         // B2
};

void createSliceTwistPruneTable(void) {
    memset(sliceTwistPrune, -1, sizeof(sliceTwistPrune));
    sliceTwistPrune[425][0] = 0;  // solved: slice edges in positions 4-7, twist=0

    int done  = 1;
    int prev  = 0;
    int depth = 0;

    while (done > prev) {
        prev = done;
        //printf("  [sliceTwist] depth=%d, done=%d\n", depth, done);
        for (int slice = 0; slice < 495; slice++) {
            for (int twist = 0; twist < 2187; twist++) {
                if (sliceTwistPrune[slice][twist] != depth) continue;
                for (int m = 0; m < 18; m++) {
                    int nSlice = udSliceMove[slice][m];
                    int nTwist = twistMove[twist][m];
                    if (sliceTwistPrune[nSlice][nTwist] == -1) {
                        sliceTwistPrune[nSlice][nTwist] = depth + 1;
                        done++;
                    }
                }
            }
        }
        depth++;
    }
    //printf("  [sliceTwist] complete, reachable=%d\n", done);
}

void createSliceFlipPruneTable(void) {
    memset(sliceFlipPrune, -1, sizeof(sliceFlipPrune));
    sliceFlipPrune[425][0] = 0;  // solved: slice edges in positions 4-7, flip=0

    int done  = 1;
    int prev  = 0;
    int depth = 0;

    while (done > prev) {
        prev = done;
        //printf("  [sliceFlip] depth=%d, done=%d\n", depth, done);
        for (int slice = 0; slice < 495; slice++) {
            for (int flip = 0; flip < 2048; flip++) {
                if (sliceFlipPrune[slice][flip] != depth) continue;
                for (int m = 0; m < 18; m++) {
                    int nSlice = udSliceMove[slice][m];
                    int nFlip  = flipMove[flip][m];
                    if (sliceFlipPrune[nSlice][nFlip] == -1) {
                        sliceFlipPrune[nSlice][nFlip] = depth + 1;
                        done++;
                    }
                }
            }
        }
        depth++;
    }
    //printf("  [sliceFlip] complete, reachable=%d\n", done);
}

void createCornPermSlicePruneTable(void) {
    memset(cornPermSlicePrune, -1, sizeof(cornPermSlicePrune));
    cornPermSlicePrune[0][0] = 0;

    int done  = 1;
    int prev  = 0;
    int depth = 0;

    while (done > prev) {
        prev = done;
        //printf("  [cornPermSlice] depth=%d, done=%d\n", depth, done);
        for (int cornerPerm = 0; cornerPerm < 40320; cornerPerm++) {
            for (int slice = 0; slice < 24; slice++) {
                if (cornPermSlicePrune[cornerPerm][slice] != depth) continue;
                for (int mi = 0; mi < 10; mi++) {
                    int m   = phase2Moves[mi];
                    int ncp = cornPermMove[cornerPerm][m];
                    int nsp = udSliceSortedMove[slice][m] % 24;
                    if (cornPermSlicePrune[ncp][nsp] == -1) {
                        cornPermSlicePrune[ncp][nsp] = depth + 1;
                        done++;
                    }
                }
            }
        }
        depth++;
    }
    //printf("  [cornPermSlice] complete, reachable=%d\n", done);
}

void createEdge8PermSlicePruneTable(void) {
    memset(edge8PermSlicePrune, -1, sizeof(edge8PermSlicePrune));
    edge8PermSlicePrune[0][0] = 0;
    int done = 1, prev = 0, depth = 0;

    while (done > prev) {
        prev = done;
        for (int ep = 0; ep < 40320; ep++) {
            for (int sl = 0; sl < 24; sl++) {
                if (edge8PermSlicePrune[ep][sl] != depth) continue;
                for (int mi = 0; mi < 10; mi++) {
                    int m = phase2Moves[mi];
                    int nep = edge8PermMove[ep][m];
                    int nsl = udSliceSortedMove[sl][m] % 24; // Use index % 24
                    if (edge8PermSlicePrune[nep][nsl] == -1) {
                        edge8PermSlicePrune[nep][nsl] = depth + 1;
                        done++;
                    }
                }
            }
        }
        depth++;
    }
}

void createPruningTables(void) {
    //printf("beginning prune tables\n");
    createSliceTwistPruneTable();
    createSliceFlipPruneTable();
    createCornPermSlicePruneTable();
    createEdge8PermSlicePruneTable();
    //printf("pruning tables complete\n");
}