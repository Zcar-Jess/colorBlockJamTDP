#include "MoveDown.h"
#include <iostream>

MoveDown::MoveDown(int blockId, int steps)
    : Operation("D" + std::to_string(blockId) + "," + std::to_string(steps),
                blockId, steps)
{}

bool MoveDown::isAppl(Board* b, int currentStep) const {
    return b->canMove(blockId, 'D', steps, currentStep);
}

Board* MoveDown::apply(Board* b, int currentStep) const {
    Board* newBoard = new Board(*b);
    newBoard->moveBlock(blockId, 'D', steps, currentStep);
    if (newBoard->canExit(blockId, currentStep)) {
        newBoard->removeBlock(blockId);
    }
    return newBoard;
}

void MoveDown::print() const {
    std::cout << "D" << blockId << "," << steps;
}