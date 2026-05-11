#include "Solver.h"

#include "Heap.h"
#include "ClosedSet.h"
#include "NeighborGenerator.h"

#include <iostream>
#include <chrono>

GameState* Solver::solve(Board* initialBoard) {

    Heap open(128);

    ClosedSet closed(128);

    GameState* start = new GameState(
        new Board(*initialBoard),
        0,
        0,
        nullptr,
        nullptr
    );

    open.push(start);

    while (!open.isEmpty()) {

        GameState* current = open.pop();

        // evitar revisitas
        if (closed.contains(current)) {
            continue;
        }

        closed.add(current);

        // objetivo alcanzado
        if (current->board->isGoal()) {
            return current;
        }

        // limite de pasos
        if (current->currentStep >
            current->board->stepLimit) {
            continue;
        }

        // generar vecinos
        int count = 0;

        GameState** neighbors =
            NeighborGenerator::generate(current, count);

        for (int i = 0; i < count; i++) {

            GameState* next = neighbors[i];

            if (!closed.contains(next)) {
                open.push(next);
            }
        }

        delete[] neighbors;
    }

    return nullptr;
}

void Solver::printSolution(GameState* goal) {

    if (!goal) {
        std::cout << "Juego sin solucion\n";
        return;
    }

    GameState* path[1024];

    int size = 0;

    GameState* cur = goal;

    while (cur != nullptr) {
        path[size++] = cur;
        cur = cur->parent;
    }

    std::cout << "Solucion encontrada.\n";

    std::cout << "Pasos:\n";

    // -------------------------------------------------
    // imprimir secuencia compacta
    // -------------------------------------------------

    for (int i = size - 2; i >= 0; i--) {

        if (path[i]->lastOp) {
            path[i]->lastOp->print();
        }
    }

    std::cout << "\n";

    // -------------------------------------------------
    // mostrar evolucion visual del tablero
    // -------------------------------------------------

    std::cout << "\n===== VISUALIZACION =====\n";

    for (int i = size - 1; i >= 0; i--) {

        path[i]->board->display(
            path[i]->currentStep
        );

        if (path[i]->lastOp) {
            path[i]->lastOp->print();
            std::cout << "\n";
        }

        std::cout << "-------------------\n";
    }
}