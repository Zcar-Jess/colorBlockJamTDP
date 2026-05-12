#include "GameState.h"
#include <iostream>

// Constructor
GameState::GameState(Board* b, int step, int g,
                     GameState* parent, Operation* lastOp)
    : board(b), currentStep(step), g(g),
      parent(parent), lastOp(lastOp)
{
    // Calcular heuristica al crear el estado
    h = computeHeuristic();
}

// Destructor: solo libera el tablero propio.
// El Solver es responsable de liberar los GameState.
GameState::~GameState() {
    delete board;
}

// ------------------------------------------------------------
// f = g + h
// ------------------------------------------------------------
int GameState::f() const {
    return g + h;
}

// heuristica: cantidad de bloques restantes.
//
// Es admisible (nunca sobreestima) porque cada bloque necesita
// al menos 1 movimiento para salir del tablero.
//
// Heuristica mas sofisticada (mejora futura): sumar la distancia
// Manhattan de cada bloque a su salida mas cercana del mismo color.
int GameState::computeHeuristic() const {
    int total = 0;

    for (int i = 0; i < board->numBlocks; i++) {

        Block* blk     = board->blocks[i];
        int    bestDist = 999999;

        for (int j = 0; j < board->numExits; j++) {

            Exit& ex = board->exits[j];

            if (ex.color != blk->color) continue;

            int dx = blk->x - ex.x;
            int dy = blk->y - ex.y;
            int dist = (dx < 0 ? -dx : dx) + (dy < 0 ? -dy : dy);

            if (dist < bestDist) bestDist = dist;
        }

        if (bestDist == 999999) bestDist = 1000;

        total += bestDist;
    }

    return total;
}

// equals: compara si dos estados tienen el mismo tablero.
//
// Dos estados son iguales si:
//  Tienen la misma cantidad de bloques
//  Cada bloque esta en la misma posicion
//
// ##### No comparamos currentStep porque el mismo tablero
// en distintos pasos es un estado diferente para las compuertas.
bool GameState::equals(const GameState* other) const {
    if (!other) return false;
    if (currentStep != other->currentStep) return false;

    Board* b1 = board;
    Board* b2 = other->board;

    // Diferente cantidad de bloques → distinto estado
    if (b1->numBlocks != b2->numBlocks) return false;

    // Comparar cada bloque por id y posicion
    for (int i = 0; i < b1->numBlocks; i++) {
        Block* blk1 = b1->blocks[i];
        bool found  = false;

        for (int j = 0; j < b2->numBlocks; j++) {
            Block* blk2 = b2->blocks[j];
            if (blk1->id == blk2->id &&
                blk1->x  == blk2->x  &&
                blk1->y  == blk2->y) {
                found = true;
                break;
            }
        }
        if (!found) return false;
    }
    return true;
}

// print
void GameState::print() const {
    std::cout << "GameState: step=" << currentStep
              << " g=" << g << " h=" << h << " f=" << f()
              << " bloques=" << board->numBlocks << "\n";
    if (lastOp) {
        std::cout << "  ultima op: ";
        lastOp->print();
        std::cout << "\n";
    }
    board->display(currentStep);
}