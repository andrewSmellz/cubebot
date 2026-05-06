//
// Created by andre on 2026-04-25.
//
#include "cube.h"
#define SCRAMBLE_LEN 50
cube_t newSolvedCube() {
    cube_t cube;
    for (int i=0;i<8;i++) {
        cube.cornerPerm[i]=i;
        cube.cornerOren[i]=0;
    }
    for (int i=0;i<12;i++) {
        cube.edgePerm[i]=i;
        cube.edgeOren[i]=0;
    }
    return cube;
}

void displayCube(const cube_t *c) {
    printf("Corners:\n");
    for (int i = 0; i < 8; i++)
        printf("  [%d] perm=%d oren=%d\n", i, c->cornerPerm[i], c->cornerOren[i]);
    printf("Edges:\n");
    for (int i = 0; i < 12; i++)
        printf("  [%d] perm=%d oren=%d\n", i, c->edgePerm[i], c->edgeOren[i]);
}

int checkSolvedCube(const cube_t *c) {
    for (int i=0;i<8;i++) if (c->cornerPerm[i]!=i || c->cornerOren[i]!=0){return 0;}

    for (int i=0;i<12;i++) if (c->edgePerm[i]!=i || c->edgeOren[i]!=0){return 0;}

    return 1;
}

int checkIfSolvable(const cube_t *c) {
    int cornerSum = 0;
    int edgeSum = 0;

    for (int i = 0; i < 8; i++) cornerSum += c->cornerOren[i];

    for (int i = 0; i < 12; i++) edgeSum += c->edgeOren[i];

    return (cornerSum % 3 == 0) && (edgeSum % 2 == 0);
}

void cubeMoveU(cube_t *c) {
    uint8_t temp = c->cornerPerm[0];
    c->cornerPerm[0] = c->cornerPerm[1];
    c->cornerPerm[1] = c->cornerPerm[2];
    c->cornerPerm[2] = c->cornerPerm[3];
    c->cornerPerm[3] = temp;

    temp = c->edgePerm[0];
    c->edgePerm[0] = c->edgePerm[1];
    c->edgePerm[1] = c->edgePerm[2];
    c->edgePerm[2] = c->edgePerm[3];
    c->edgePerm[3] = temp;
}

void cubeMoveD(cube_t *c) {
    uint8_t temp = c->cornerPerm[4];
    c->cornerPerm[4] = c->cornerPerm[7];
    c->cornerPerm[7] = c->cornerPerm[6];
    c->cornerPerm[6] = c->cornerPerm[5];
    c->cornerPerm[5] = temp;

    temp = c->edgePerm[8];
    c->edgePerm[8] = c->edgePerm[11];
    c->edgePerm[11] = c->edgePerm[10];
    c->edgePerm[10] = c->edgePerm[9];
    c->edgePerm[9] = temp;
}

void cubeMoveF(cube_t *c) {
    uint8_t temp = c->cornerPerm[0];
    c->cornerPerm[0] = c->cornerPerm[4];
    c->cornerPerm[4] = c->cornerPerm[5];
    c->cornerPerm[5] = c->cornerPerm[1];
    c->cornerPerm[1] = temp;

    temp = c->cornerOren[0];
    c->cornerOren[0] = (c->cornerOren[4]+1) % 3;
    c->cornerOren[4] = (c->cornerOren[5]+2) % 3;
    c->cornerOren[5] = (c->cornerOren[1]+1) % 3;
    c->cornerOren[1] = (temp+2)%3;

    temp = c->edgePerm[1];
    c->edgePerm[1] = c->edgePerm[4];
    c->edgePerm[4] = c->edgePerm[8];
    c->edgePerm[8] = c->edgePerm[5];
    c->edgePerm[5] = temp;

    temp = c->edgeOren[1];
    c->edgeOren[1] = c->edgeOren[4]^1;
    c->edgeOren[4] = c->edgeOren[8]^1;
    c->edgeOren[8] = c->edgeOren[5]^1;
    c->edgeOren[5] = temp^1;
}

void cubeMoveB(cube_t *c) {
    uint8_t temp = c->cornerPerm[3];
    c->cornerPerm[3] = c->cornerPerm[7];
    c->cornerPerm[7] = c->cornerPerm[6];
    c->cornerPerm[6] = c->cornerPerm[2];
    c->cornerPerm[2] = temp;

    temp = c->cornerOren[3];
    c->cornerOren[3] = (c->cornerOren[7]+2) % 3;
    c->cornerOren[7] = (c->cornerOren[6]+1) % 3;
    c->cornerOren[6] = (c->cornerOren[2]+2) % 3;
    c->cornerOren[2] = (temp+1)%3;

    temp = c->edgePerm[3];
    c->edgePerm[3] = c->edgePerm[7];
    c->edgePerm[7] = c->edgePerm[10];
    c->edgePerm[10] = c->edgePerm[6];
    c->edgePerm[6] = temp;

    temp = c->edgeOren[3];
    c->edgeOren[3] = c->edgeOren[7]^1;
    c->edgeOren[7] = c->edgeOren[10]^1;
    c->edgeOren[10] = c->edgeOren[6]^1;
    c->edgeOren[6] = temp^1;
}

void cubeMoveR(cube_t *c) {
    uint8_t temp = c->cornerPerm[0];
    c->cornerPerm[0] = c->cornerPerm[4];
    c->cornerPerm[4] = c->cornerPerm[7];
    c->cornerPerm[7] = c->cornerPerm[3];
    c->cornerPerm[3] = temp;

    temp = c->cornerOren[0];
    c->cornerOren[0] = (c->cornerOren[4]+2) % 3;
    c->cornerOren[4] = (c->cornerOren[7]+1) % 3;
    c->cornerOren[7] = (c->cornerOren[3]+2) % 3;
    c->cornerOren[3] = (temp+1)%3;

    temp = c->edgePerm[0];
    c->edgePerm[0] = c->edgePerm[4];
    c->edgePerm[4] = c->edgePerm[11];
    c->edgePerm[11] = c->edgePerm[7];
    c->edgePerm[7] = temp;

    temp = c->edgeOren[0];
    c->edgeOren[0] = c->edgeOren[4];
    c->edgeOren[4] = c->edgeOren[11];
    c->edgeOren[11] = c->edgeOren[7];
    c->edgeOren[7] = temp;
}

void cubeMoveL(cube_t *c) {
    uint8_t temp = c->cornerPerm[1];
    c->cornerPerm[1] = c->cornerPerm[2];
    c->cornerPerm[2] = c->cornerPerm[6];
    c->cornerPerm[6] = c->cornerPerm[5];
    c->cornerPerm[5] = temp;

    temp = c->cornerOren[1];
    c->cornerOren[1] = (c->cornerOren[2]+2) % 3;
    c->cornerOren[2] = (c->cornerOren[6]+1) % 3;
    c->cornerOren[6] = (c->cornerOren[5]+2) % 3;
    c->cornerOren[5] = (temp+1)%3;

    temp = c->edgePerm[2];
    c->edgePerm[2] = c->edgePerm[6];
    c->edgePerm[6] = c->edgePerm[9];
    c->edgePerm[9] = c->edgePerm[5];
    c->edgePerm[5] = temp;

    temp = c->edgeOren[2];
    c->edgeOren[2] = c->edgeOren[6];
    c->edgeOren[6] = c->edgeOren[9];
    c->edgeOren[9] = c->edgeOren[5];
    c->edgeOren[5] = temp;
}

void cubeMoveU2(cube_t *c){cubeMoveU(c);cubeMoveU(c);}
void cubeMoveD2(cube_t *c){cubeMoveD(c);cubeMoveD(c);}
void cubeMoveF2(cube_t *c){cubeMoveF(c);cubeMoveF(c);}
void cubeMoveB2(cube_t *c){cubeMoveB(c);cubeMoveB(c);}
void cubeMoveR2(cube_t *c){cubeMoveR(c);cubeMoveR(c);}
void cubeMoveL2(cube_t *c){cubeMoveL(c);cubeMoveL(c);}

//TODO make proper prime moves to save 2 moves lol
void cubeMoveUP(cube_t *c){cubeMoveU(c);cubeMoveU(c);cubeMoveU(c);}
void cubeMoveDP(cube_t *c){cubeMoveD(c);cubeMoveD(c);cubeMoveD(c);}
void cubeMoveFP(cube_t *c){cubeMoveF(c);cubeMoveF(c);cubeMoveF(c);}
void cubeMoveBP(cube_t *c){cubeMoveB(c);cubeMoveB(c);cubeMoveB(c);}
void cubeMoveRP(cube_t *c){cubeMoveR(c);cubeMoveR(c);cubeMoveR(c);}
void cubeMoveLP(cube_t *c){cubeMoveL(c);cubeMoveL(c);cubeMoveL(c);}

void cubeApplyMove(cube_t * c, move_t m) {
    switch (m) {
        case U1: cubeMoveU(c); break;  case U2: cubeMoveU2(c); break; case UP: cubeMoveUP(c); break;
        case R1: cubeMoveR(c); break;  case R2: cubeMoveR2(c); break; case RP: cubeMoveRP(c); break;
        case F1: cubeMoveF(c); break;  case F2: cubeMoveF2(c); break; case FP: cubeMoveFP(c); break;
        case D1: cubeMoveD(c); break;  case D2: cubeMoveD2(c); break; case DP: cubeMoveDP(c); break;
        case L1: cubeMoveL(c); break;  case L2: cubeMoveL2(c); break; case LP: cubeMoveLP(c); break;
        case B1: cubeMoveB(c); break;  case B2: cubeMoveB2(c); break; case BP: cubeMoveBP(c); break;
    }
}

void cubeTurnFace(cube_t *c, int face) {
    switch (face) {
        case 0: cubeMoveU(c); break;
        case 1: cubeMoveR(c); break;
        case 2: cubeMoveF(c); break;
        case 3: cubeMoveD(c); break;
        case 4: cubeMoveL(c); break;
        case 5: cubeMoveB(c); break;
    }
}

char* scrambleCube(cube_t *c) {
    static char scramble[SCRAMBLE_LEN+1];
    for (int i=0; i<SCRAMBLE_LEN;i++) {
        const int move = rand() % 6;
        switch (move) {
            case 0:
                cubeMoveU(c);
                scramble[i] = 'U';
                break;
            case 1:
                cubeMoveD(c);
                scramble[i] = 'D';
                break;
            case 2:
                cubeMoveF(c);
                scramble[i] = 'F';
                break;
            case 3:
                cubeMoveB(c);
                scramble[i] = 'B';
                break;
            case 4:
                cubeMoveR(c);
                scramble[i] = 'R';
                break;
            case 5:
                cubeMoveL(c);
                scramble[i] = 'L';
                break;

        }
    }
    scramble[SCRAMBLE_LEN] = '\0';
    return scramble;
}

void sexyLoop(cube_t *c) {
    for (int i =0; i<24; i++) {
        cubeMoveR(c);
        cubeMoveU(c);
        cubeMoveRP(c);
        cubeMoveUP(c);
    }
}
