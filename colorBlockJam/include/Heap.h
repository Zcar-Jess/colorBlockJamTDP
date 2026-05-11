#ifndef HEAP_H
#define HEAP_H

#include "GameState.h"

// Heap: cola de prioridad minima (min-heap) de GameState*.
// Equivalente al Heap del ejemplo del profe pero con GameState.
//
// Ordena los estados por f = g + h (menor f = mayor prioridad).
// Es el OpenSet del algoritmo A*: siempre extrae el estado mas
// prometedor para explorar primero.
//
// Implementacion: arreglo con indices basados en 1.
//   - Padre de i: i/2
//   - Hijo izq de i: 2*i
//   - Hijo der de i: 2*i+1

class Heap {
public:
    GameState** arr;   // arreglo de punteros a GameState
    int size;          // cantidad de elementos actuales
    int capacity;      // capacidad maxima del arreglo

    // Constructor: crea un heap vacio con la capacidad dada
    Heap(int capacity);

    // Destructor: libera el arreglo (NO los GameState, los libera el Solver)
    ~Heap();

    // Inserta un GameState en el heap manteniendo la propiedad de min-heap
    void push(GameState* s);

    // Extrae y retorna el GameState con menor f (la raiz del heap)
    GameState* pop();

    // Retorna true si el heap esta vacio
    bool isEmpty() const;

    // Muestra el heap por consola (para debug)
    void print() const;

private:
    // Sube el elemento en 'index' hasta su posicion correcta
    // (se usa despues de push)
    void heapifyUp(int index);

    // Baja el elemento en 'index' hasta su posicion correcta
    // (se usa despues de pop)
    void heapifyDown(int index);
};

#endif