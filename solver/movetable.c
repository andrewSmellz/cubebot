//
// Created by andre on 2026-04-30.
//

#include "movetable.h"
int twistMove[2187][18];
int flipMove[2048][18];
int udSliceMove[495][18];
int cornPermMove[40320][18];
int udSliceSortedMove[11880][18];
int edge8PermMove[40320][18];

void createMoveTables(void) {
    //printf("beginning move table creation\n");
    cube_t c;

    for (int i = 0; i < 2187; i++) {
        c = newSolvedCube();
        invertCornerOrientationCoordinate(&c, i);
        for (int j = 0; j < 6; j++) {
            for (int k = 0; k < 4; k++) {
                cubeTurnFace(&c, j);
                if (k < 3) twistMove[i][3*j+k] = cornerOrientationCoordinate(&c);
            }
        }
    }

    for (int i = 0; i < 2048; i++) {
        c = newSolvedCube();
        invertEdgeOrientationCoordinate(&c, i);
        for (int j = 0; j < 6; j++) {
            for (int k = 0; k < 4; k++) {
                cubeTurnFace(&c, j);
                if (k < 3) flipMove[i][3*j+k] = edgeOrientationCoordinate(&c);
            }
        }
    }

    for (int i = 0; i < 495; i++) {
        c = newSolvedCube();
        invertUDSliceCoordinate(&c, i);
        for (int j = 0; j < 6; j++) {
            for (int k = 0; k < 4; k++) {
                cubeTurnFace(&c, j);
                if (k < 3) udSliceMove[i][3*j+k] = udSliceCoordinate(&c);
            }
        }
    }

    for (int i = 0; i < 40320; i++) {
    c = newSolvedCube();
        invertCornerPermutationCoordinate(&c, i);
        for (int j = 0; j < 6; j++) {
            for (int k = 0; k < 4; k++) {
                cubeTurnFace(&c, j);
                if (k < 3) cornPermMove[i][3*j+k] = cornerPermutationCoordinate(&c);
            }
        }
    }

    for (int i = 0; i < 11880; i++) {
        c = newSolvedCube();
        invertUDSliceCoordinate2(&c, i);
        for (int j = 0; j < 6; j++) {
            for (int k = 0; k < 4; k++) {
                cubeTurnFace(&c, j);
                if (k < 3) udSliceSortedMove[i][3*j+k] = udSliceCoordinate2(&c);
            }
        }
    }

    for (int i = 0; i < 40320; i++) {
        c = newSolvedCube();
        invertEdge8PermutationCoordinate(&c, i);
        for (int j = 0; j < 6; j++) {
            for (int k = 0; k < 4; k++) {
                cubeTurnFace(&c, j);
                if (k < 3) edge8PermMove[i][3*j+k] = edge8PermutationCoordinate(&c);
            }
        }
    }

    //printf("move tables complete\n");
}