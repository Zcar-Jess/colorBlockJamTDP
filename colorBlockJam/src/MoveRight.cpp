#include "MoveRight.h"
#include <iostream>

MoveRight::MoveRight(int blockId, int steps)
    : Operation("R" + std::to_string(blockId) + "," + std::to_string(steps),
                blockId, steps)
{}

bool MoveRight::isAppl(Board* b, int currentStep) const {
    return b->canMove(blockId, 'R', steps, currentStep);
}

Board* MoveRight::apply(Board* b, int currentStep) const {
    Board* newBoard = new Board(*b);
    newBoard->moveBlock(blockId, 'R', steps, currentStep);
    return newBoard;
}

void MoveRight::print() const {
    std::cout << "R" << blockId << "," << steps;
}