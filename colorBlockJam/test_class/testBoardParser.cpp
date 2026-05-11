#include "BoardParser.h"
#include "Solver.h"

#include <iostream>

int main() {

    Board* board =
        BoardParser::loadFromFile(
            "data/test/simple1.txt"
        );

    if (!board) {

        std::cout << "Error cargando archivo";

        return 1;
    }

    std::cout << "===== TABLERO =====";

    board->display(0);

    GameState* goal =
        Solver::solve(board);

    Solver::printSolution(goal);

    delete board;

    return 0;
}