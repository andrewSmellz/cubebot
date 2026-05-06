#include "movetable.h"
#include "pruning.h"
#include "tests.h"

int main(void) {
    createMoveTables();
    createPruningTables();

    runTests();

    return 0;
}
