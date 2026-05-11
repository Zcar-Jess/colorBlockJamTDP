#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "Board.h"
#include "Operation.h"

// GameState: representa un nodo del grafo que explora A*.
//
// Contiene:
//   - El tablero actual (posiciones de bloques en ese instante)
//   - El paso de tiempo actual (afecta compuertas y salidas)
//   - El costo g: cuantos movimientos se hicieron hasta aqui
//   - El valor h: heuristica (estimacion de pasos al objetivo)
//   - Puntero al padre: para reconstruir el camino al final
//   - La operacion que genero este estado (para mostrar solucion)
//
// La funcion de evaluacion de A* es f = g + h.
// El Heap ordena los GameState por f (menor f = mayor prioridad).

class GameState {
public:
    Board*      board;      // tablero en este estado (memoria propia)
    int         currentStep;// paso de tiempo actual
    int         g;          // costo acumulado (cantidad de movimientos)
    int         h;          // valor heuristico estimado
    GameState*  parent;     // estado padre (null si es el inicial)
    Operation*  lastOp;     // operacion que genero este estado (null si inicial)

    // Constructor
    GameState(Board* board, int currentStep, int g,
              GameState* parent, Operation* lastOp);

    // Destructor: libera el tablero (solo el de este estado)
    ~GameState();

    // Retorna f = g + h (valor de evaluacion para el Heap)
    int f() const;

    // Calcula la heuristica h.
    // Heuristica: cantidad de bloques restantes en el tablero.
    // Es admisible porque cada bloque necesita al menos 1 movimiento para salir.
    // Entre mas bloques queden, mas lejos estamos del objetivo.
    int computeHeuristic() const;

    // Retorna true si los dos estados tienen el mismo tablero.
    // Usado por el Stack (ClosedSet) para no revisitar estados.
    // Dos tableros son iguales si todos los bloques estan en la misma posicion.
    bool equals(const GameState* other) const;

    // Muestra el estado por consola (para debug)
    void print() const;
};

#endif