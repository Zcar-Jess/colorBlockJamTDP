#include "Solver.h"

#include <iostream>

int main() {

    Board board(
        "solverTest",
        8,
        8,
        50,
        10,
        10,
        10
    );

    // =========================
    // PAREDES
    // =========================

    for (int i = 0; i < 8; i++) {

        board.grid[0][i].setAsWall();
        board.grid[7][i].setAsWall();

        board.grid[i][0].setAsWall();

        // dejar espacio para salida
        if (i != 4 && i != 5) {
            board.grid[i][7].setAsWall();
        }
    }

    // =========================
    // BLOQUE 2x2
    // =========================

    bool* geo = new bool[4];

    geo[0] = true;
    geo[1] = true;
    geo[2] = true;
    geo[3] = true;

    Block* b = new Block(
        1,      // id
        'a',    // color
        2,      // width
        2,      // height
        4,      // x (fila)
        4,      // y (columna)
        0,      // colorLock
        geo
    );

    board.addBlock(b);

    // =========================
    // SALIDA
    // =========================

    Exit ex(
        'a',    // color
        4,      // x
        7,      // y
        'V',    // orientacion
        2,      // li
        2,      // lf
        0       // step
    );

    board.addExit(ex);

    // =========================
    // DISPLAY
    // =========================

    std::cout << "TABLERO INICIAL\n";

    board.display(0);

    // =========================
    // SOLVER
    // =========================

    GameState* goal =
        Solver::solve(&board);

    // =========================
    // RESULTADO
    // =========================

    Solver::printSolution(goal);

    return 0;
}