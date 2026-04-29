//
// Created by andre on 2026-04-28.
//

#include "solver.h"

int cornerOrientationCoordinate(const cube_t *c) {
    int coord=0;
    for(int i=0;i<7;i++) {
        coord=coord*3 + c->cornerOren[i];
    }
    return coord;
}

int edgeOrientationCoordinate(const cube_t *c) {
    int coord=0;
    for(int i=0;i<11;i++) {
        coord=coord*2 + c->edgeOren[i];
    }
    return coord;
}

//there is 12 edges, and you need to check 4 so at most it can be 12C4, hence hardcoded lookup table
static const int nCk[13][5] = {
    {1, 0,  0,   0,   0},
    {1, 1,  0,   0,   0},
    {1, 2,  1,   0,   0},
    {1, 3,  3,   1,   0},
    {1, 4,  6,   4,   1},
    {1, 5, 10,  10,   5},
    {1, 6, 15,  20,  15},
    {1, 7, 21,  35,  35},
    {1, 8, 28,  56,  70},
    {1, 9, 36,  84, 126},
    {1,10, 45, 120, 210},
    {1,11, 55, 165, 330},
    {1,12, 66, 220, 495},
};



int udSliceCoordinate(const cube_t *c) {
    int occupied[12]={0};
    for (int i=0;i<12;i++) {
        if (c->edgePerm[i]>=4 && c->edgePerm[i]<=7) {
            occupied[i]=1;
        }
    }
    int coord=0;
    int k=3;
    int n=11;
    while (k>=0) {
        if (occupied[n]==1) {
            k--;
        }else {
            coord+=nCk[n][k];
        }
        n--;
    }
    return coord;
}
