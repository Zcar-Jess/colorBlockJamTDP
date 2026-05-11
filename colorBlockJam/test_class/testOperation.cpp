#include "Board.h"
#include "MoveUp.h"
#include "MoveDown.h"
#include "MoveLeft.h"
#include "MoveRight.h"
#include <iostream>
#include <cassert>

// Construye el tablero
Board* buildBoard() {
    Board* board = new Board("SIMPLE1", 8, 8, 50);
    for (int j = 0; j < 8; j++) { board->setWall(0,j); board->setWall(7,j); }
    for (int i = 0; i < 8; i++) { board->setWall(i,0); board->setWall(i,7); }
    Exit e('a', 4, 7, 'V', 2, 2, 0);
    board->addExit(e);
    bool geom[] = {true, true, true, true};
    Block* b = new Block(1, 'a', 2, 2, 4, 4, 0, geom);
    board->addBlock(b);
    return board;
}

void testNombres() {
    std::cout << "[TEST] Nombres de operaciones...\n";

    MoveRight r(1, 2);
    MoveLeft  l(2, 1);
    MoveUp    u(1, 3);
    MoveDown  d(3, 1);

    assert(r.name == "R1,2");
    assert(l.name == "L2,1");
    assert(u.name == "U1,3");
    assert(d.name == "D3,1");

    std::cout << "  PASSED\n";
}

void testIsAppl() {
    std::cout << "[TEST] isAppl() — operaciones validas e invalidas...\n";

    Board* b = buildBoard();

    // El bloque esta en (4,4), puede moverse a la derecha 1 celda
    MoveRight r1(1, 1);
    assert(r1.isAppl(b, 0) == true);

    // No puede moverse a la izquierda (hay pared en col 0 y espacio libre)
    // En realidad si puede moverse a la izquierda desde col 4
    MoveLeft l1(1, 1);
    assert(l1.isAppl(b, 0) == true);

    // No puede moverse hacia arriba mas de 3 celdas (hay pared en fila 0)
    MoveUp u5(1, 5);
    assert(u5.isAppl(b, 0) == false);

    delete b;
    std::cout << "  PASSED\n";
}

void testApply() {
    std::cout << "[TEST] apply() genera nuevo Board sin modificar el original...\n";

    Board* original = buildBoard();
    MoveDown d(1, 1);  // mover abajo, no toca la salida

    Board* resultado = d.apply(original, 0);

    // El original NO debe haberse modificado (sigue en fila 4)
    assert(original->grid[4][4].isBlockPart() == true);
    assert(original->grid[5][4].isBlockPart() == true);

    // El resultado SI debe tener el bloque movido (ahora en filas 5 y 6)
    assert(resultado->grid[4][4].isEmpty()     == true);  // fila vieja limpia
    assert(resultado->grid[5][4].isBlockPart() == true);  // nueva posicion
    assert(resultado->grid[5][5].isBlockPart() == true);
    assert(resultado->grid[6][4].isBlockPart() == true);
    assert(resultado->grid[6][5].isBlockPart() == true);

    // El bloque NO salio (sigue en el tablero)
    assert(resultado->numBlocks == 1);

    delete original;
    delete resultado;
    std::cout << "  PASSED\n";
}

void testSolucionPDF() {
    std::cout << "[TEST] Solucion del PDF: R1,1 → bloque sale...\n";

    Board* b = buildBoard();
    MoveRight r(1, 1);

    assert(r.isAppl(b, 0) == true);

    // Aplicar: el bloque queda adyacente a la salida y sale
    Board* resultado = r.apply(b, 0);

    // El tablero resultado debe estar vacio (bloque salio)
    assert(resultado->isGoal() == true);

    delete b;
    delete resultado;
    std::cout << "  PASSED\n";
}

void testPrint() {
    std::cout << "[TEST] print() — salida visual:\n";
    MoveRight r(1, 1);
    r.print();
    std::cout << "\n  (verificar visualmente)\n";
}

int main() {
    std::cout << "=== Tests de Operation (Move) ===\n";
    testNombres();
    testIsAppl();
    testApply();
    testSolucionPDF();
    testPrint();
    std::cout << "\nTodos los tests de Operation pasaron OK.\n";
    return 0;
}