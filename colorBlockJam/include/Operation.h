#ifndef OPERATION_H
#define OPERATION_H

#include <string>
#include "Board.h"

// Operation: clase base para todas las operaciones.
// Cada operacion representa un movimiento posible:
//   MoveUp, MoveDown, MoveLeft, MoveRight
// El algoritmo A* genera todas las operaciones aplicables
// sobre un estado (Board) y las usa para generar vecinos.

class Operation {
public:
    std::string name;   // nombre descriptivo, ej: "R1,2" (bloque 1, 2 celdas derecha)
    int blockId;        // ID del bloque a mover
    int steps;          // cantidad de celdas a mover

    // Constructor
    Operation();
    Operation(const std::string& name, int blockId, int steps);

    // Destructor
    virtual ~Operation();

    // Retorna true si la operacion es aplicable sobre el tablero
    // en el paso de tiempo currentStep.
    virtual bool isAppl(Board* b, int currentStep) const;

    // Aplica la operacion sobre el tablero y retorna un nuevo Board
    // con el resultado (copia del tablero con el movimiento aplicado).
    // El llamador es responsable de liberar la memoria del Board retornado.
    virtual Board* apply(Board* b, int currentStep) const;

    // Muestra la operacion por consola (para test)
    virtual void print() const;
};

#endif