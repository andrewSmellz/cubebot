#include "movetable.h"
#include "pruning.h"
#include "solver.h"
#include "tests.h"

int main(void) {
    createMoveTables();
    createPruningTables();

    cube_t cube = newSolvedCube();
    char* scramble = scrambleCube(&cube);
    printf("the scramble is: %s\n", scramble);

    move_t solution[35];
    solve(&cube, solution);

    printf("the solution  is: \n");

    printMoves(solution);
    printf("\n");

    for (int i = 0; solution[i] != (move_t)-1; i++) {
        cubeApplyMove(&cube, solution[i]);
    }

    printf("solved:%d",checkSolvedCube(&cube));

    return 0;
}
