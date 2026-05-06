//
// Created by andre on 2026-05-06.
//

#include "pruning.h"
#include <string.h>

int sliceTwistPrune[495][2187];
int sliceFlipPrune[495][2048];
int cornPermSlicePrune[40320][24];

static const int phase2Moves[10] = {
    0, 1, 2,   // U1, U2, U'
    4,         // R2
    7,         // F2
    9, 10, 11, // D1, D2, D'
    13,        // L2
    16         // B2
};


void createSliceTwistPruneTable(void) {
    memset(sliceTwistPrune, -1, sizeof(sliceTwistPrune));//everything set to -1 meaning unvisited
    sliceTwistPrune[0][0]=0;// solved state is 0 moves away

    int done  = 1;
    int total = 495 * 2187;
    int depth = 0;

    while (done < total) {
        for (int slice = 0; slice < 495; slice++) {
            for (int twist = 0; twist < 2187; twist++) {
                if (sliceTwistPrune[slice][twist] != depth) continue;
                for (int m=0; m<18; m++) {
                    int nSlice = udSliceMove[slice][m];
                    int nTwist = twistMove[twist][m];
                    if (sliceTwistPrune[nSlice][nTwist] == -1) {
                        sliceTwistPrune[nSlice][nTwist] = depth+1;
                        done++;
                    }
                }
            }
        }
        depth++;
    }
}

void createSliceFlipPruneTable(void) {
    memset(sliceFlipPrune, -1, sizeof(sliceFlipPrune));
    sliceFlipPrune[0][0]=0;

    int done  = 1;
    int total = 495 * 2048;
    int depth = 0;

    while (done < total) {
        for (int slice = 0; slice < 495; slice++) {
            for (int flip = 0; flip < 2048; flip++) {
                if (sliceFlipPrune[slice][flip] != depth) continue;
                for (int m=0; m<18; m++) {
                    int nSlice = udSliceMove[slice][m];
                    int nFlip = flipMove[flip][m];
                    if (sliceFlipPrune[nSlice][nFlip] == -1) {
                        sliceFlipPrune[nSlice][nFlip] = depth+1;
                        done++;
                    }
                }
            }
        }
        depth++;
    }
}
void createCornPermSlicePruneTable(void) {
    memset(cornPermSlicePrune, -1, sizeof(cornPermSlicePrune));
    cornPermSlicePrune[0][0]=0;

    int done  = 1;
    int total = 40320 * 24;
    int depth = 0;

    while (done < total) {
        for (int cornerPerm = 0; cornerPerm < 40320; cornerPerm++) {
            for (int slice = 0; slice < 24; slice++) {
                if (cornPermSlicePrune[cornerPerm][slice] != depth) continue;
                for (int mi = 0; mi < 10; mi++) {
                    int m   = phase2Moves[mi];
                    int ncp = cornPermMove[cornerPerm][m];
                    int nsp = udSliceSortedMove[slice][m] % 24;
                    if (cornPermSlicePrune[ncp][nsp] == -1) {
                        cornPermSlicePrune[ncp][nsp] =depth+1;
                        done++;
                    }
                }
            }
        }
        depth++;
    }
}

void createPruningTables(void) {
    createSliceTwistPruneTable();
    createSliceFlipPruneTable();
    createCornPermSlicePruneTable();
}