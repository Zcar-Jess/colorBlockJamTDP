#ifndef SOLVER_H
#define SOLVER_H

#include "GameState.h"

class Solver {
public:

    static GameState* solve(Board* initialBoard);

    static void printSolution(GameState* goal);

    static void printOperations(GameState* goal);
};

#endif