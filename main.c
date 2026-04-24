#include <stdio.h>
#include "cube.h"

cube_t newSolvedCube() {
    cube_t cube = {0};
    for (int i = 0; i < 12; i++) {
        cube.edges |= (uint64_t)(i <<(i*5));
    }
    for (int i = 0; i < 8; i++) {
        cube.edges |= (uint64_t)(i <<(i*5));
    }

    return cube;
}


int main(void) {
    printf("Hello, World!\n");
    return 0;
}