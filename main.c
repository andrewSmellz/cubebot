#include <stdio.h>
#include "cube.h"



int main(void) {
    cube_t c = newSolvedCube();
    char* scramble = scrambleCube(&c);
    printf("%s\n", scramble);
    printf("valid: %d\n", checkSolvedCube(&c));
    return 0;
}
