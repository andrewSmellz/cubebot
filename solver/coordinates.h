//
// Created by andre on 2026-04-28.
//

#ifndef CUBEBOT_COORDINATES_H
#define CUBEBOT_COORDINATES_H
#include "cube.h"

int cornerOrientationCoordinate(const cube_t *c);
int edgeOrientationCoordinate(const cube_t *c);
int udSliceCoordinate(const cube_t *c);

int cornerPermutationCoordinate(const cube_t *c);
int edgePermutationCoordinate(const cube_t *c);
int udSliceCoordinate2(const cube_t *c);

void invertCornerOrientationCoordinate(cube_t *c, int coord);
void invertEdgeOrientationCoordinate(cube_t *c, int coord);
void invertUDSliceCoordinate(cube_t *c, int coord);

void invertCornerPermutationCoordinate(cube_t *c, int coord);
void invertEdgePermutationCoordinate(cube_t *c, int coord);
void invertUDSliceCoordinate2(cube_t *c, int coord);

int edge8PermutationCoordinate(const cube_t *c);
void invertEdge8PermutationCoordinate(cube_t *c, int coord);

#endif //CUBEBOT_COORDINATES_H
