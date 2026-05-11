#include "GameState.h"
#include "Heap.h"
#include "MoveRight.h"
#include <iostream>
#include <cassert>

// ------------------------------------------------------------
// Construye el tablero del ejemplo del PDF
// ------------------------------------------------------------
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

void testGameStateBasico() {
    std::cout << "[TEST] GameState basico...\n";

    Board* b = buildBoard();
    GameState* gs = new GameState(b, 0, 0, nullptr, nullptr);

    assert(gs->g           == 0);
    assert(gs->currentStep == 0);
    assert(gs->parent      == nullptr);
    assert(gs->lastOp      == nullptr);

    // La heuristica
    assert(gs->h >= 0);
    assert(gs->f() == gs->g + gs->h);
    delete gs;
    std::cout << "  PASSED\n";
}

void testGameStateEquals() {
    std::cout << "[TEST] equals() entre estados...\n";

    Board* b1 = buildBoard();
    Board* b2 = buildBoard();

    GameState* gs1 = new GameState(b1, 0, 0, nullptr, nullptr);
    GameState* gs2 = new GameState(b2, 0, 0, nullptr, nullptr);

    // Mismo tablero, mismo paso → iguales
    assert(gs1->equals(gs2) == true);

    // Mover bloque en gs2
    gs2->board->moveBlock(1, 'L', 1, 0);

    // Ahora son distintos
    assert(gs1->equals(gs2) == false);

    delete gs1;
    delete gs2;
    std::cout << "  PASSED\n";
}

void testHeapOrden() {

    std::cout << "[TEST] Heap ordena por f = g + h...\n";

    Heap heap(10);

    Board* b1 = buildBoard();
    Board* b2 = buildBoard();
    Board* b3 = buildBoard();

    GameState* gs1 =
        new GameState(b1, 0, 5, nullptr, nullptr);

    GameState* gs2 =
        new GameState(b2, 0, 1, nullptr, nullptr);

    GameState* gs3 =
        new GameState(b3, 0, 3, nullptr, nullptr);

    heap.push(gs1);
    heap.push(gs2);
    heap.push(gs3);

    assert(heap.size == 3);

    GameState* primero = heap.pop();
    GameState* segundo = heap.pop();
    GameState* tercero = heap.pop();

    // Deben salir ordenados por f creciente
    assert(primero->f() <= segundo->f());
    assert(segundo->f() <= tercero->f());

    assert(heap.isEmpty() == true);

    delete primero;
    delete segundo;
    delete tercero;

    std::cout << "  PASSED\n";
}

void testHeapIsEmpty() {
    std::cout << "[TEST] Heap isEmpty y pop en heap vacio...\n";

    Heap heap(5);
    assert(heap.isEmpty() == true);
    assert(heap.pop()     == nullptr);

    Board* b = buildBoard();
    GameState* gs = new GameState(b, 0, 0, nullptr, nullptr);
    heap.push(gs);
    assert(heap.isEmpty() == false);

    heap.pop();
    assert(heap.isEmpty() == true);

    delete gs;
    std::cout << "  PASSED\n";
}

void testPrint() {
    std::cout << "[TEST] print() — salida visual:\n";
    Board* b = buildBoard();
    GameState* gs = new GameState(b, 0, 0, nullptr, nullptr);
    gs->print();
    delete gs;
    std::cout << "  (verificar visualmente)\n";
}

int main() {
    std::cout << "=== Tests de GameState y Heap ===\n";
    testGameStateBasico();
    testGameStateEquals();
    testHeapOrden();
    testHeapIsEmpty();
    testPrint();
    std::cout << "\nTodos los tests de GameState y Heap pasaron OK.\n";
    return 0;
}