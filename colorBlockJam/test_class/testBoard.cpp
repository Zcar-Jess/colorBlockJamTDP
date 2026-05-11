#include "Board.h"
#include <iostream>
#include <cassert>

// ------------------------------------------------------------
// testBoard.cpp — prueba unitaria de la clase Board
// Usa el ejemplo exacto del PDF:
//   Tablero 8x8, bloque 2x2 color 'a' en (4,4)
//   Salida color 'a' en columna 7, orientacion V, largo 2
//   Solucion: R1,1 (mover bloque 1 una celda a la derecha)
//
// Compilar: make testBoard
// ------------------------------------------------------------

// Construye el tablero del ejemplo del PDF
Board* buildExampleBoard() {
    Board* board = new Board("SIMPLE1", 8, 8, 50);

    // Paredes del borde (########)
    for (int j = 0; j < 8; j++) {
        board->setWall(0, j); // fila superior
        board->setWall(7, j); // fila inferior
    }
    for (int i = 0; i < 8; i++) {
        board->setWall(i, 0); // columna izquierda
        board->setWall(i, 7); // columna derecha (con salida en filas 4-5)
    }

    // Salida: COLOR=a X=4 Y=7 ORIENTATION=V LI=2 LF=2 STEP=0
    Exit e('a', 4, 7, 'V', 2, 2, 0);
    board->addExit(e);

    // Bloque 1: color='a', 2x2, posicion (4,4), geometria llena
    bool geom[] = {true, true, true, true};
    Block* b = new Block(1, 'a', 2, 2, 4, 4, 0, geom);
    board->addBlock(b);

    return board;
}

void testInicializacion() {
    std::cout << "[TEST] Inicializacion del tablero...\n";

    Board* board = buildExampleBoard();

    assert(board->width     == 8);
    assert(board->height    == 8);
    assert(board->stepLimit == 50);
    assert(board->numBlocks == 1);
    assert(board->numExits  == 1);
    assert(board->numGates  == 0);

    // Las paredes del borde deben ser WALL
    assert(board->grid[0][0].isWall() == true);
    assert(board->grid[7][7].isWall() == true);

    // El bloque debe ocupar celdas (4,4)(4,5)(5,4)(5,5)
    assert(board->grid[4][4].isBlockPart() == true);
    assert(board->grid[4][5].isBlockPart() == true);
    assert(board->grid[5][4].isBlockPart() == true);
    assert(board->grid[5][5].isBlockPart() == true);

    // La salida debe estar marcada en (4,7)
    assert(board->grid[4][7].isExit() == true);

    delete board;
    std::cout << "  PASSED\n";
}

void testMoverBloque() {
    std::cout << "[TEST] Mover bloque a la derecha (R1,1)...\n";

    Board* board = buildExampleBoard();

    // Verificar que puede moverse 1 celda a la derecha
    assert(board->canMove(1, 'R', 1, 0) == true);

    // Mover
    int moved = board->moveBlock(1, 'R', 1, 0);
    assert(moved == 1);

    // Las celdas viejas deben estar vacias
    assert(board->grid[4][4].isEmpty() == true);
    assert(board->grid[5][4].isEmpty() == true);

    // Las celdas nuevas deben estar ocupadas
    assert(board->grid[4][5].isBlockPart() == true);
    assert(board->grid[4][6].isBlockPart() == true);
    assert(board->grid[5][5].isBlockPart() == true);
    assert(board->grid[5][6].isBlockPart() == true);

    delete board;
    std::cout << "  PASSED\n";
}

void testCanExit() {
    std::cout << "[TEST] Bloque puede salir tras moverse...\n";

    Board* board = buildExampleBoard();

    // Antes de moverse, NO puede salir
    assert(board->canExit(1, 0) == false);

    // Mover 1 celda a la derecha: queda adyacente a la salida
    board->moveBlock(1, 'R', 1, 0);

    // Ahora SI puede salir
    assert(board->canExit(1, 0) == true);

    delete board;
    std::cout << "  PASSED\n";
}

void testRemoveBlock() {
    std::cout << "[TEST] Eliminar bloque del tablero...\n";

    Board* board = buildExampleBoard();
    board->moveBlock(1, 'R', 1, 0);
    board->removeBlock(1);

    // El tablero debe estar sin bloques
    assert(board->numBlocks == 0);
    assert(board->isGoal()  == true);

    // Las celdas deben estar vacias
    assert(board->grid[4][5].isEmpty() == true);
    assert(board->grid[5][6].isEmpty() == true);

    delete board;
    std::cout << "  PASSED\n";
}

void testIsGoal() {
    std::cout << "[TEST] isGoal()...\n";

    Board* board = buildExampleBoard();

    assert(board->isGoal() == false); // hay un bloque

    board->moveBlock(1, 'R', 1, 0);
    board->removeBlock(1);

    assert(board->isGoal() == true);  // no quedan bloques

    delete board;
    std::cout << "  PASSED\n";
}

void testDisplay() {
    std::cout << "[TEST] display() — estado inicial:\n";
    Board* board = buildExampleBoard();
    board->display(0);
    std::cout << "\n  Despues de R1,1:\n";
    board->moveBlock(1, 'R', 1, 0);
    board->display(0);
    delete board;
    std::cout << "  (verificar visualmente)\n";
}

int main() {
    std::cout << "=== Tests de Board ===\n";
    testInicializacion();
    testMoverBloque();
    testCanExit();
    testRemoveBlock();
    testIsGoal();
    testDisplay();
    std::cout << "\nTodos los tests de Board pasaron OK.\n";
    return 0;
}