#include <iostream>
#include <chrono>
#include "BoardParser.h"
#include "Solver.h"
#include "MoveSequence.h"
#include "ClosedSet.h"

using namespace std;

Board*     currentBoard = nullptr;
GameState* solution     = nullptr;
ClosedSet* closedSet    = nullptr;  // para liberar memoria al salir

void cargarArchivo() {
    // liberar estado anterior
    if (closedSet)    { delete closedSet;    closedSet = nullptr; }
    if (currentBoard) { delete currentBoard; currentBoard = nullptr; }
    solution = nullptr;

    string path;
    cout << "Ingrese archivo: ";
    cin >> path;
    path = "data/test/" + path;

    currentBoard = BoardParser::loadFromFile(path.c_str());
    if (!currentBoard) { cout << "Error cargando archivo\n"; return; }

    cout << "\nTablero cargado:\n";
    currentBoard->display(0);
}

void resolver() {
    if (!currentBoard) { cout << "Primero cargue un tablero\n"; return; }

    // liberar solucion anterior
    if (closedSet) { delete closedSet; closedSet = nullptr; }
    solution = nullptr;

    auto inicio = chrono::high_resolution_clock::now();
    solution = Solver::solve(currentBoard);
    auto fin  = chrono::high_resolution_clock::now();

    auto ms = chrono::duration_cast<chrono::milliseconds>(fin - inicio);
    cout << "\nTiempo resolucion: " << ms.count() << " [mseg]\n";

    if (!solution) { cout << "Juego sin solucion\n"; return; }

    cout << "Solucion encontrada.\nPasos:\n";
    Solver::printOperations(solution);
}

void mostrarSolucion() {
    if (!solution) { cout << "No hay solucion cargada\n"; return; }
    Solver::printSolution(solution);
}

void aplicarSecuencia() {
    if (!currentBoard) { cout << "Primero cargue un tablero\n"; return; }
    string seq;
    cout << "Ingrese secuencia (ej: R1,1U2,3): ";
    cin >> seq;
    cout << "\nTablero inicial:\n";
    currentBoard->display(0);
    cout << "-------------------\n";
    MoveSequence::apply(currentBoard, seq.c_str());
}

int main() {
    int op = -1;
    while (op != 0) {
        cout << "\n===== COLOR BLOCK JAM =====\n";
        cout << "1. Cargar archivo\n";
        cout << "2. Resolver tablero\n";
        cout << "3. Mostrar solucion paso a paso\n";
        cout << "4. Aplicar secuencia de movimientos\n";
        cout << "0. Salir\n";
        cout << "Opcion: ";
        cin >> op;

        switch (op) {
            case 1: cargarArchivo();   break;
            case 2: resolver();        break;
            case 3: mostrarSolucion(); break;
            case 4: aplicarSecuencia(); break;
            case 0:
                // Liberar toda la memoria antes de salir
                if (closedSet)    delete closedSet;
                if (currentBoard) delete currentBoard;
                cout << "Saliendo...\n";
                break;
            default:
                cout << "Opcion invalida\n";
        }
    }
    return 0;
}