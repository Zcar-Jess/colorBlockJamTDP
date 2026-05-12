#include "NeighborGenerator.h"
#include "MoveUp.h"
#include "MoveDown.h"
#include "MoveLeft.h"
#include "MoveRight.h"

GameState** NeighborGenerator::generate(
    GameState* current,
    int& outCount
) {
    Board* board       = current->board;
    int    capacity    = board->numBlocks * 4 + 8;
    GameState** neighbors = new GameState*[capacity];
    outCount = 0;

    char dirs[4] = {'U', 'D', 'L', 'R'};

    for (int i = 0; i < board->numBlocks; i++) {

        int id     = board->blocks[i]->id;
        int maxDim = board->width > board->height
                     ? board->width : board->height;

        for (int d = 0; d < 4; d++) {

            char dir = dirs[d];

            // Encontrar el maximo deslizamiento posible
            // (el bloque se desliza hasta chocar)
            int maxSteps = 0;
            for (int s = 1; s <= maxDim; s++) {
                if (board->canMove(id, dir, s, current->currentStep)) {
                    maxSteps = s;
                } else {
                    break;
                }
            }

            // Solo generar vecino si hay movimiento posible
            if (maxSteps == 0) continue;

            Operation* op = nullptr;
            switch (dir) {
                case 'U': op = new MoveUp   (id, maxSteps); break;
                case 'D': op = new MoveDown  (id, maxSteps); break;
                case 'L': op = new MoveLeft  (id, maxSteps); break;
                case 'R': op = new MoveRight (id, maxSteps); break;
            }

            // Aplicar movimiento
            Board* nextBoard = op->apply(board, current->currentStep);
            int    nextStep  = current->currentStep + maxSteps;

            // Verificar salida con el paso CORRECTO (nextStep)
            if (nextBoard->canExit(id, nextStep)) {
                nextBoard->removeBlock(id);
            }

            GameState* nextState = new GameState(
                nextBoard,
                nextStep,
                current->g + maxSteps,
                current,
                op
            );

            // Expandir arreglo si es necesario
            if (outCount >= capacity) {
                capacity *= 2;
                GameState** newArr = new GameState*[capacity];
                for (int k = 0; k < outCount; k++)
                    newArr[k] = neighbors[k];
                delete[] neighbors;
                neighbors = newArr;
            }

            neighbors[outCount++] = nextState;
        }
    }

    return neighbors;
}