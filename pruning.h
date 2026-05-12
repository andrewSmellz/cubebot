//
// Created by andre on 2026-05-06.
//

#ifndef CUBEBOT_PRUNING_H
#define CUBEBOT_PRUNING_H
#include "movetable.h"

extern int8_t   sliceTwistPrune[495][2187];
extern int8_t   sliceFlipPrune[495][2048];
extern int8_t   cornPermSlicePrune[40320][24];
extern int8_t edge8PermSlicePrune[40320][24];

void createSliceTwistPruneTable(void);
void createSliceFlipPruneTable(void);
void createCornPermSlicePruneTable(void);
void createEdge8PermSlicePruneTable(void);

void createPruningTables(void);



#endif //CUBEBOT_PRUNING_H
