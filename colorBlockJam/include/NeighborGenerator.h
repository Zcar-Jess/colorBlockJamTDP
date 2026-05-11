#ifndef NEIGHBORGENERATOR_H
#define NEIGHBORGENERATOR_H

#include "GameState.h"

class NeighborGenerator {
public:

    // Genera todos los vecinos válidos.
    //
    // Retorna arreglo dinámico de punteros GameState*.
    // outCount indica cantidad de vecinos generados.

    static GameState** generate(
        GameState* current,
        int& outCount
    );
};

#endif