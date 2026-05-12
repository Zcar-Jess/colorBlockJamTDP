#ifndef CLOSEDSET_H
#define CLOSEDSET_H

#include "GameState.h"

// Nodo para chaining en la tabla hash
struct HashNode {
    GameState* state;
    HashNode*  next;
    HashNode(GameState* s) : state(s), next(nullptr) {}
};

// ClosedSet implementado como HashTable con chaining.
// Operaciones add() y contains() en O(1) promedio.
// La clave de hash se calcula desde las posiciones de los bloques.
class ClosedSet {
public:
    HashNode** buckets;  // arreglo de listas enlazadas
    int        numBuckets;
    int        size;

    ClosedSet(int numBuckets = 256);
    ~ClosedSet();

    // Agrega un estado al conjunto
    void add(GameState* s);

    // Retorna true si ya existe un estado equivalente
    bool contains(GameState* s) const;

private:
    // Calcula el hash de un GameState a partir de
    // las posiciones de sus bloques y el paso actual
    int computeHash(GameState* s) const;
};

#endif