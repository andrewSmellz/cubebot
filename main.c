#include <stdio.h>
#include "cube.h"



int main(void) {
    cube_t c = newSolvedCube();
    sexy(&c);
    printf("valid: %d\n", checkSolvedCube(&c));
    return 0;
}

