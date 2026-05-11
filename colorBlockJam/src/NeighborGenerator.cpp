#include "NeighborGenerator.h"

#include "MoveUp.h"
#include "MoveDown.h"
#include "MoveLeft.h"
#include "MoveRight.h"

GameState** NeighborGenerator::generate(
    GameState* current,
    int& outCount
) {

    Board* board = current->board;

    int capacity = 128;

    GameState** neighbors = new GameState*[capacity];

    outCount = 0;

    for (int i = 0; i < board->numBlocks; i++) {

        Block* blk = board->blocks[i];

        int id = blk->id;

        // probar todas las direcciones
        char dirs[4] = {'U', 'D', 'L', 'R'};

        for (int d = 0; d < 4; d++) {

            char dir = dirs[d];

            // probar todas las distancias posibles
            for (int steps = 1; steps <= 10; steps++) {

                if (!board->canMove(
                        id,
                        dir,
                        steps,
                        current->currentStep
                    )) {
                    break;
                }

                Operation* op = nullptr;

                switch(dir) {
                    case 'U':
                        op = new MoveUp(id, steps);
                        break;

                    case 'D':
                        op = new MoveDown(id, steps);
                        break;

                    case 'L':
                        op = new MoveLeft(id, steps);
                        break;

                    case 'R':
                        op = new MoveRight(id, steps);
                        break;
                }

                Board* nextBoard = op->apply(
                    board,
                    current->currentStep
                );

                int nextStep = current->currentStep + steps;

                // verificar salida ANTES de crear GameState
                if (nextBoard->canExit(id, nextStep)) {
                    nextBoard->removeBlock(id);
                }

                GameState* nextState = new GameState(
                    nextBoard,
                    nextStep,
                    current->g + steps,
                    current,
                    op
                );

                if (outCount >= capacity) {

                    capacity *= 2;

                    GameState** newArr =
                        new GameState*[capacity];

                    for (int k = 0; k < outCount; k++) {
                        newArr[k] = neighbors[k];
                    }

                    delete[] neighbors;
                    neighbors = newArr;
                }

                neighbors[outCount++] = nextState;
            }
        }
    }

    return neighbors;
}