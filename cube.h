//
// Created by andrew on 4/22/26.
//

#ifndef CUBEBOT_CUBE_H
#define CUBEBOT_CUBE_H
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>



/**
 * Cubie ordering as follows:
 * Corners:     Edges:
 * 0: URF       0: UR
 * 1: UFL       1: UF
 * 2: ULB       2: UL
 * 3: UBR       3: UB
 * 4: DFR       4: FR
 * 5: DLF       5: FL
 * 6: DBL       6: BL
 * 7: DRB       7: BR
 *              8: DF
 *              9: DL
 *              10: DB
 *              11: DR
 */
typedef struct {
    uint8_t cornerPerm[8];
    uint8_t cornerOren[8];
    uint8_t edgePerm[12];
    uint8_t edgeOren[12];
}cube_t;


typedef enum {
    U1, U2, UP,
    R1, R2, RP,
    F1, F2, FP,
    D1, D2, DP,
    L1, L2, LP,
    B1, B2, BP
} move_t;

cube_t newSolvedCube();
void displayCube(const cube_t *c);
int checkSolvedCube(const cube_t *c);
int checkIfSolvable(const cube_t *c);

void cubeMoveU(cube_t *c);
void cubeMoveD(cube_t *c);
void cubeMoveF(cube_t *c);
void cubeMoveB(cube_t *c);
void cubeMoveR(cube_t *c);
void cubeMoveL(cube_t *c);

void cubeMoveU2(cube_t *c);
void cubeMoveD2(cube_t *c);
void cubeMoveF2(cube_t *c);
void cubeMoveB2(cube_t *c);
void cubeMoveR2(cube_t *c);
void cubeMoveL2(cube_t *c);

void cubeMoveUP(cube_t *c);
void cubeMoveDP(cube_t *c);
void cubeMoveFP(cube_t *c);
void cubeMoveBP(cube_t *c);
void cubeMoveRP(cube_t *c);
void cubeMoveLP(cube_t *c);

void cubeApplyMove(cube_t *c, move_t m);
void cubeTurnFace(cube_t *c, int face);

char* scrambleCube(cube_t *c);

void sexyLoop(cube_t *c);


#endif //CUBEBOT_CUBE_H