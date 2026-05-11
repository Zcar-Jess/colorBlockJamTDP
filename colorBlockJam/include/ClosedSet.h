#ifndef CLOSEDSET_H
#define CLOSEDSET_H

#include "GameState.h"

// ClosedSet simple.
// Guarda estados ya explorados para evitar revisitas.
//
// Implementación:
//   arreglo dinámico de punteros a GameState.
//
// Más adelante puede mejorarse usando hashing.

class ClosedSet {
public:
    GameState** states;
    int size;
    int capacity;

    ClosedSet(int capacity = 128);
    ~ClosedSet();

    // Agrega un estado al conjunto
    void add(GameState* s);

    // Retorna true si ya existe un estado equivalente
    bool contains(GameState* s) const;
};

#endif