#include "Solver.h"
#include "Heap.h"
#include "ClosedSet.h"
#include "NeighborGenerator.h"
#include <iostream>
#include <chrono>

GameState* Solver::solve(Board* initialBoard) {

    Heap*      open   = new Heap(512);
    ClosedSet* closed = new ClosedSet(1024);

    GameState* start = new GameState(
        new Board(*initialBoard), 0, 0, nullptr, nullptr
    );

    open->push(start);

    GameState* solution = nullptr;

    while (!open->isEmpty()) {

        GameState* current = open->pop();

        // Estado ya visitado: liberar y saltar
        if (closed->contains(current)) {
            delete current;
            continue;
        }

        // Agregar al ClosedSet (toma ownership)
        closed->add(current);

        // Objetivo alcanzado
        if (current->board->isGoal()) {
            solution = current;
            break;
        }

        // Limite de pasos
        if (current->currentStep > current->board->stepLimit) {
            continue;
        }

        // Generar vecinos
        int count = 0;
        GameState** neighbors =
            NeighborGenerator::generate(current, count);

        for (int i = 0; i < count; i++) {
            if (!closed->contains(neighbors[i])) {
                open->push(neighbors[i]);
            } else {
                delete neighbors[i];
            }
        }

        delete[] neighbors;
    }

    // Liberar estados restantes en el Heap (no visitados)
    while (!open->isEmpty()) {
        GameState* gs = open->pop();
        if (!closed->contains(gs)) {
            delete gs;
        }
    }

    // ClosedSet contiene todos los estados visitados incluyendo
    // el camino solucion. NO liberar el ClosedSet aqui para que
    // los punteros parent del camino solucion sigan validos.
    // Se liberan en printSolution despues de usar la solucion.
    delete open;
    // closed se libera desde main despues de usar la solucion

    return solution;
}

void Solver::printSolution(GameState* goal) {

    if (!goal) {
        std::cout << "No hay solucion\n";
        return;
    }

    // Reconstruir camino usando arreglo en heap (no stack)
    int capacity = 1024;
    GameState** path = new GameState*[capacity];
    int size = 0;

    GameState* cur = goal;
    while (cur != nullptr) {
        if (size >= capacity) {
            capacity *= 2;
            GameState** newPath = new GameState*[capacity];
            for (int i = 0; i < size; i++) newPath[i] = path[i];
            delete[] path;
            path = newPath;
        }
        path[size++] = cur;
        cur = cur->parent;
    }

    std::cout << "===== VISUALIZACION =====\n";
    path[size - 1]->board->display(path[size - 1]->currentStep);

    for (int i = size - 2; i >= 0; i--) {
        if (path[i]->lastOp) {
            path[i]->lastOp->print();
            std::cout << "\n";
        }
        path[i]->board->display(path[i]->currentStep);
        std::cout << "-------------------\n";
    }

    delete[] path;
}

void Solver::printOperations(GameState* goal) {

    if (!goal) return;

    int capacity = 1024;
    GameState** path = new GameState*[capacity];
    int size = 0;

    GameState* cur = goal;
    while (cur != nullptr) {
        if (size >= capacity) {
            capacity *= 2;
            GameState** newPath = new GameState*[capacity];
            for (int i = 0; i < size; i++) newPath[i] = path[i];
            delete[] path;
            path = newPath;
        }
        path[size++] = cur;
        cur = cur->parent;
    }

    for (int i = size - 2; i >= 0; i--) {
        if (path[i]->lastOp) {
            path[i]->lastOp->print();
        }
    }
    std::cout << "\n";

    delete[] path;
}