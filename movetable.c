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
    for (int i=0; i<2187; i++) {
        cube_t cube = newSolvedCube();
        invertCornerOrientationCoordinate(&cube, i);
        for (int j=0; j<6; j++) {
            for (int k=0; k<3; k++) {
                cubeTurnFace(&cube,j);
                twistMove[i][3*j+k] = cornerOrientationCoordinate(&cube);
            }
            cubeTurnFace(&cube,j);
        }
    }

    for (int i=0; i<2048; i++) {
        cube_t cube = newSolvedCube();
        invertEdgeOrientationCoordinate(&cube, i);
        for (int j=0; j<6; j++) {
            for (int k=0; k<3; k++) {
                cubeTurnFace(&cube,j);
                flipMove[i][3*j+k] = edgeOrientationCoordinate(&cube);
            }
            cubeTurnFace(&cube,j);
        }
    }

    for (int i=0; i<495; i++) {
        cube_t cube = newSolvedCube();
        invertUDSliceCoordinate(&cube, i);
        for (int j=0; j<6; j++) {
            for (int k=0; k<3; k++) {
                cubeTurnFace(&cube,j);
                udSliceMove[i][3*j+k] = udSliceCoordinate(&cube);
            }
            cubeTurnFace(&cube,j);
        }
    }

    for (int i=0; i<40320; i++) {
        cube_t cube = newSolvedCube();
        invertCornerPermutationCoordinate(&cube, i);
        for (int j=0; j<6; j++) {
            for (int k=0; k<3; k++) {
                cubeTurnFace(&cube,j);
                cornPermMove[i][3*j+k] = cornerPermutationCoordinate(&cube);
            }
            cubeTurnFace(&cube,j);
        }
    }

    for (int i=0; i<11880; i++) {
        cube_t cube = newSolvedCube();
        invertUDSliceCoordinate2(&cube, i);
        for (int j=0; j<6; j++) {
            for (int k=0; k<3; k++) {
                cubeTurnFace(&cube,j);
                udSliceSortedMove[i][3*j+k] = udSliceCoordinate2(&cube);
            }
            cubeTurnFace(&cube,j);
        }
    }
}