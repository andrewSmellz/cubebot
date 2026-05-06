//
// Created by andre on 2026-04-30.
//

#include "movetable.h"
int twistMove[2187][18];
int flipMove[2048][18];
int udSliceMove[495][18];
int cornPermMove[40320][18];
int udSliceSortedMove[11880][18];

void createMoveTables(void) {
    cube_t c;

    c = newSolvedCube();
    for (int i = 0; i < 2187; i++) {
        invertCornerOrientationCoordinate(&c, i);
        for (int j = 0; j < 6; j++) {
            for (int k = 0; k < 4; k++) {
                cubeTurnFace(&c, j);
                if (k < 3) twistMove[i][3*j+k] = cornerOrientationCoordinate(&c);
            }
        }
    }

    c = newSolvedCube();
    for (int i = 0; i < 2048; i++) {
        invertEdgeOrientationCoordinate(&c, i);
        for (int j = 0; j < 6; j++) {
            for (int k = 0; k < 4; k++) {
                cubeTurnFace(&c, j);
                if (k < 3) flipMove[i][3*j+k] = edgeOrientationCoordinate(&c);
            }
        }
    }

    c = newSolvedCube();
    for (int i = 0; i < 495; i++) {
        invertUDSliceCoordinate(&c, i);
        for (int j = 0; j < 6; j++) {
            for (int k = 0; k < 4; k++) {
                cubeTurnFace(&c, j);
                if (k < 3) udSliceMove[i][3*j+k] = udSliceCoordinate(&c);
            }
        }
    }

    c = newSolvedCube();
    for (int i = 0; i < 40320; i++) {
        invertCornerPermutationCoordinate(&c, i);
        for (int j = 0; j < 6; j++) {
            for (int k = 0; k < 4; k++) {
                cubeTurnFace(&c, j);
                if (k < 3) cornPermMove[i][3*j+k] = cornerPermutationCoordinate(&c);
            }
        }
    }

    c = newSolvedCube();
    for (int i = 0; i < 11880; i++) {
        invertUDSliceCoordinate2(&c, i);
        for (int j = 0; j < 6; j++) {
            for (int k = 0; k < 4; k++) {
                cubeTurnFace(&c, j);
                if (k < 3) udSliceSortedMove[i][3*j+k] = udSliceCoordinate2(&c);
            }
        }
    }
}