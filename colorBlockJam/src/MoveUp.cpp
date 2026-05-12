#include "MoveUp.h"
#include <iostream>

MoveUp::MoveUp(int blockId, int steps)
    : Operation("U" + std::to_string(blockId) + "," + std::to_string(steps),
                blockId, steps)
{}

bool MoveUp::isAppl(Board* b, int currentStep) const {
    return b->canMove(blockId, 'U', steps, currentStep);
}

Board* MoveUp::apply(Board* b, int currentStep) const {
    // Crear copia del tablero (A* no modifica el estado original)
    Board* newBoard = new Board(*b);
    newBoard->moveBlock(blockId, 'U', steps, currentStep);
    return newBoard;
}

void MoveUp::print() const {
    std::cout << "U" << blockId << "," << steps;
}