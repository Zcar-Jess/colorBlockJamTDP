#include <iostream>
#include <chrono>

#include "BoardParser.h"
#include "Solver.h"

using namespace std;

Board* currentBoard = nullptr;
GameState* solution = nullptr;

void cargarArchivo() {

    string path;

    cout << "Ingrese archivo: ";
    cin >> path;

    path = "data/test/" + path;

    if (currentBoard != nullptr) {
        delete currentBoard;
        currentBoard = nullptr;
    }

    currentBoard = BoardParser::loadFromFile(path.c_str());

    if (currentBoard == nullptr) {
        cout << "Error cargando archivo\n";
        return;
    }

    cout << "\nTablero cargado:\n";
    currentBoard->display(0);
}

void resolver() {

    if (currentBoard == nullptr) {
        cout << "Primero cargue un tablero\n";
        return;
    }

    auto inicio = chrono::high_resolution_clock::now();

    solution = Solver::solve(currentBoard);

    auto fin = chrono::high_resolution_clock::now();

    auto tiempo =
        chrono::duration_cast<chrono::milliseconds>(
            fin - inicio
        );

    cout << "\nTiempo resolucion: "
         << tiempo.count()
         << " [mseg]\n";

    if (solution == nullptr) {
        cout << "Juego sin solucion\n";
        return;
    }

    cout << "Solucion encontrada.\n";
    cout << "Pasos:\n";

    Solver::printOperations(solution);
}

void mostrarSolucion() {

    if (solution == nullptr) {
        cout << "No hay solucion cargada\n";
        return;
    }

    Solver::printSolution(solution);
}

int main() {

    int op = -1;

    while (op != 0) {

        cout << "\n===== COLOR BLOCK JAM =====\n";
        cout << "1. Cargar archivo\n";
        cout << "2. Resolver tablero\n";
        cout << "3. Mostrar solucion\n";
        cout << "0. Salir\n";
        cout << "Opcion: ";

        cin >> op;

        switch (op) {

            case 1:
                cargarArchivo();
                break;

            case 2:
                resolver();
                break;

            case 3:
                mostrarSolucion();
                break;

            case 0:
                cout << "Saliendo...\n";
                break;

            default:
                cout << "Opcion invalida\n";
        }
    }

    return 0;
}