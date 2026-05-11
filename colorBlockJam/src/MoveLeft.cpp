#include "MoveLeft.h"
#include <iostream>

MoveLeft::MoveLeft(int blockId, int steps)
    : Operation("L" + std::to_string(blockId) + "," + std::to_string(steps),
                blockId, steps)
{}

bool MoveLeft::isAppl(Board* b, int currentStep) const {
    return b->canMove(blockId, 'L', steps, currentStep);
}

Board* MoveLeft::apply(Board* b, int currentStep) const {
    Board* newBoard = new Board(*b);
    newBoard->moveBlock(blockId, 'L', steps, currentStep);
    if (newBoard->canExit(blockId, currentStep)) {
        newBoard->removeBlock(blockId);
    }
    return newBoard;
}

void MoveLeft::print() const {
    std::cout << "L" << blockId << "," << steps;
}