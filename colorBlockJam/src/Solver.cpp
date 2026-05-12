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
        std::cout << "No hay solucion\n";
        return;
    }

    GameState* path[1024];

    int size = 0;

    GameState* cur = goal;

    while (cur != nullptr) {
        path[size++] = cur;
        cur = cur->parent;
    }

    std::cout << "===== VISUALIZACION =====\n";

    // tablero inicial
    path[size - 1]->board->display(
        path[size - 1]->currentStep
    );

    // desde el segundo estado en adelante
    for (int i = size - 2; i >= 0; i--) {

        // imprimir movimiento
        if (path[i]->lastOp) {
            path[i]->lastOp->print();
            std::cout << "\n";
        }

        // imprimir tablero resultante
        path[i]->board->display(
            path[i]->currentStep
        );

        std::cout << "-------------------\n";
    }
}

void Solver::printOperations(GameState* goal) {

    if (goal == nullptr) {
        return;
    }

    GameState* path[1024];

    int size = 0;

    GameState* cur = goal;

    while (cur != nullptr) {
        path[size++] = cur;
        cur = cur->parent;
    }

    for (int i = size - 2; i >= 0; i--) {

        if (path[i]->lastOp) {
            path[i]->lastOp->print();
        }
    }

    std::cout << "\n";
}