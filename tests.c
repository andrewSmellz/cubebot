//
// Created by andre on 2026-05-06.
//

#include "tests.h"

void coordinatesTests(void) {
    printf("Coordinates testing:\n");

    // Corner orientation: 0..2186
    for (int i = 0; i < 2187; i++) {
        cube_t c = newSolvedCube();
        invertCornerOrientationCoordinate(&c, i);
        assert(cornerOrientationCoordinate(&c) == i);
    }
    printf("test 1 passed!\n");


    // Edge orientation: 0..2047
    for (int i = 0; i < 2048; i++) {
        cube_t c = newSolvedCube();
        invertEdgeOrientationCoordinate(&c, i);
        assert(edgeOrientationCoordinate(&c) == i);
    }
    printf("test 2 passed!\n");

    // UD slice: 0..494
    for (int i = 0; i < 495; i++) {
        cube_t c = newSolvedCube();
        invertUDSliceCoordinate(&c, i);
        assert(udSliceCoordinate(&c) == i);
    }
    printf("test 3 passed!\n");

    // Corner permutation: 0..40319
    for (int i = 0; i < 40320; i++) {
        cube_t c = newSolvedCube();
        invertCornerPermutationCoordinate(&c, i);
        assert(cornerPermutationCoordinate(&c) == i);
    }
    printf("test 4 passed!\n");

    // Edge permutation: 0..479001599
    // Too large to exhaustively test - sample instead
    for (int i = 0; i < 479001600; i ++) {
        cube_t c = newSolvedCube();
        invertEdgePermutationCoordinate(&c, i);
        assert(edgePermutationCoordinate(&c) == i);
    }
    printf("test 5 passed!\n");

    // UD slice sorted: 0..11879
    for (int i = 0; i < 11880; i++) {
        cube_t c = newSolvedCube();
        invertUDSliceCoordinate2(&c, i);
        assert(udSliceCoordinate2(&c) == i);
    }
    printf("test 6 passed!\n");

    printf("All tests passed!\n");
}

void moveTableTests(void) {
    printf("running move table tests:\n");
    createMoveTables();

    for (int i = 0; i < 2187; i++)
        for (int m = 0; m < 18; m++) {
            int c = twistMove[i][m];
            c = twistMove[c][m];
            c = twistMove[c][m];
            c = twistMove[c][m];
            if (c != i) { printf("twist FAIL: i=%d m=%d result=%d\n", i, m, c); assert(0); }

            assert(c == i);
        }
    printf("test 1 passed!\n");

    for (int i = 0; i < 2048; i++)
        for (int m = 0; m < 18; m++) {
            int c = flipMove[i][m];
            c = flipMove[c][m];
            c = flipMove[c][m];
            c = flipMove[c][m];
            assert(c == i);
        }
    printf("test 2 passed!\n");

    for (int i = 0; i < 495; i++)
        for (int m = 0; m < 18; m++) {
            int c = udSliceMove[i][m];
            c = udSliceMove[c][m];
            c = udSliceMove[c][m];
            c = udSliceMove[c][m];
            assert(c == i);
        }
    printf("test 3 passed!\n");

    for (int i = 0; i < 40320; i++)
        for (int m = 0; m < 18; m++) {
            int c = cornPermMove[i][m];
            c = cornPermMove[c][m];
            c = cornPermMove[c][m];
            c = cornPermMove[c][m];
            assert(c == i);
        }
    printf("test 4 passed!\n");

    for (int i = 0; i < 11880; i++)
        for (int m = 0; m < 18; m++) {
            int c = udSliceSortedMove[i][m];
            c = udSliceSortedMove[c][m];
            c = udSliceSortedMove[c][m];
            c = udSliceSortedMove[c][m];
            assert(c == i);
        }
    printf("test 5 passed!\n");

    printf("All movetable tests passed!\n");
}

void runTests(void) {
    coordinatesTests();
    moveTableTests();
}