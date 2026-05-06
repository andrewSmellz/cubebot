//
// Created by andre on 2026-04-28.
//

#include "coordinates.h"

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

int cornerPermutationCoordinate(const cube_t *c) {
    int coord=0;
    for (int i=7;i>0;i--) {
        int s=0;
        for (int j=i-1;j>=0;j--) {
            if (c->cornerPerm[j] > c->cornerPerm[i]) {
                s++;
            }
        }
        coord=(coord+s)*i;

    }
    return coord;
}

int edgePermutationCoordinate(const cube_t *c) {
    int coord=0;
    for (int i=11;i>0;i--) {
        int s=0;
        for (int j=i-1;j>=0;j--) {
            if (c->edgePerm[j] > c->edgePerm[i]) {
                s++;
            }
        }
        coord=(coord+s)*i;
    }
    return coord;
}

int udSliceCoordinate2(const cube_t *c) {
    int arr[4];
    int j=0;
    for (int i=0;i<12;i++) {
        const int e = c->edgePerm[i];
        if (e >= 4 && e <= 7)
            arr[j++] = e;
    }
    int coord=0;
    for (j=3;j>0;j--) {
        int s=0;
        for (int k=j-1;k>=0;k--) {
            if (arr[k]>arr[j]) {
                s++;
            }
        }
        coord=(coord+s)*j;
    }
    return udSliceCoordinate(c)*24+coord;
}

void invertCornerOrientationCoordinate(cube_t *c, int coord) {
    int parity=0;
    for (int i=6;i>=0;i--) {
        parity=parity+coord%3;
        c->cornerOren[i]=coord%3;
        coord/=3;
    }
    parity=parity%3;
    switch (parity) {
        case 0: c->cornerOren[7] = 0; break;
        case 1: c->cornerOren[7] = 2; break;
        case 2: c->cornerOren[7] = 1; break;
    }
}

void invertEdgeOrientationCoordinate(cube_t *c, int coord) {
    int parity=0;
    for (int i=10;i>=0;i--) {
        parity=parity+coord%2;
        c->edgeOren[i]=coord%2;
        coord/=2;
    }
    c->edgeOren[11] = parity % 2;
}

void invertUDSliceCoordinate(cube_t *c, int coord) {
    int occupied[12]={0};
    int n=11;
    int k=3;
    while (k>=0) {
        int v = nCk[n][k];
        if (coord<v) {
            k--;
            occupied[n]=1;
        }else {
            coord=coord-v;
        }
        n--;
    }

    int sliceEdge = 4;//4 is FR edge
    for (int ed=0; ed<12; ed++) {
        if (occupied[ed]==1) {
            for (int i=0; i<12; i++) {
                if (c->edgePerm[i] == sliceEdge) {
                    c->edgePerm[i] = c->edgePerm[ed];
                    break;
                }
            }
            c->edgePerm[ed] = sliceEdge;
            if (sliceEdge < 7) sliceEdge++;
        }
    }
}

/**
 * https://github.com/hkociemba/CubeExplorer/blob/master/CubiCube.pas
 * InvCornPermCoord
 * InvEdgePermCoord
 * InvUDSliceSortedCoord
 */
void invertCornerPermutationCoordinate(cube_t *c, int coord) {
    int order[8];
    int used[8];
    for (int i=0;i<8;i++) {
        used[i]=0;
        order[i]=coord%(i+1);
        coord/=(i+1);
    }
    for (int i=7;i>=0;i--) {
        int k=7;
        while (used[k]) k--;
        while (order[i]>0) {
            order[i]--;
            k--;
            while (used[k]!=0) k--;
        }
        c->cornerPerm[i]=k;
        used[k]=1;
    }
}
void invertEdgePermutationCoordinate(cube_t *c, int coord) {
    int order[12];
    int used[12];
    for (int i=0;i<12;i++) {
        used[i]=0;
        order[i]=coord%(i+1);
        coord/=(i+1);
    }
    for (int i=11;i>=0;i--) {
        int k=11;
        while (used[k]) k--;
        while (order[i]>0) {
            order[i]--;
            k--;
            while (used[k]!=0) k--;
        }
        c->edgePerm[i]=k;
        used[k]=1;
    }
}
void invertUDSliceCoordinate2(cube_t *c, int coord) {
    int used[4]={0};
    int order[4];
    int x=coord%24;
    invertUDSliceCoordinate(c,coord/24);
    for (int i=0;i<4;i++) {
        order[i]=x %(i+1);
        x/=(i+1);
    }
    for (int i=3;i>=0;i--) {
        int k=3;
        while (used[k]) k--;
        while (order[i]>0) {
            order[i]--;
            k--;
            while (used[k]!=0) k--;
        }

        int m=-1;
        for (int j=0; j<12; j++) {
            int e = c->edgePerm[j];
            if (e==4 || e==5 || e==6 || e==7) m++;
            if (m==i) {
                c->edgePerm[j]=k+4;
                used[k]=1;
                break;
            }
        }
    }
}