#ifndef BOARD_H
#define BOARD_H

#include "Cell.h"
#include "Block.h"
#include "Exit.h"
#include "Gate.h"

// Board: representa el tablero completo del juego CBJ.
// Contiene la grilla de celdas (Cell), los bloques moviles,
// las salidas y las compuertas.
//
// La grilla grid[i][j] representa la celda en fila i, columna j.
// Los bloques se ubican en la grilla segun su posicion (x,y).
//
// Invariante: cada celda de la grilla refleja en todo momento
// el estado real del tablero (vacia, pared, bloque, etc.)
// ------------------------------------------------------------
// Estructura del Board:
// Board
// ├── Cell** grid        → grilla H x W de celdas
// ├── Block** blocks     → arreglo de bloques móviles
// ├── Exit*  exits       → arreglo de salidas
// ├── Gate*  gates       → arreglo de compuertas
// ├── int width, height, stepLimit
// └── char name[]

class Board {
public:
    char  name[64];   // nombre del tablero (del archivo de config)
    int   width;      // cantidad de columnas
    int   height;     // cantidad de filas
    int   stepLimit;  // maximo de pasos permitidos

    Cell**  grid;       // grilla[height][width] de celdas
    Block** blocks;     // arreglo de punteros a bloques
    int     numBlocks;  // cantidad actual de bloques en el tablero
    int     maxBlocks;  // capacidad del arreglo blocks[]

    Exit*   exits;      // arreglo de salidas
    int     numExits;   // cantidad de salidas
    int     maxExits;   // capacidad del arreglo exits[]

    Gate*   gates;      // arreglo de compuertas
    int     numGates;   // cantidad de compuertas
    int     maxGates;   // capacidad del arreglo gates[]

    // Constructor y destructor

    // Crea un tablero vacio de width x height
    // maxBlocks, maxExits, maxGates: capacidad inicial de cada arreglo
    Board(const char* name, int width, int height, int stepLimit,
          int maxBlocks = 16, int maxExits = 16, int maxGates = 16);

    // Constructor de copia: clona el tablero completo
    Board(const Board& other);

    // Destructor: libera toda la memoria dinamica
    ~Board();

    // Metodos de configuracion del tablero

    // Marca la celda (row, col) como pared simple
    void setWall(int row, int col);

    // Agrega una salida al tablero y marca su celda en la grilla
    void addExit(const Exit& exit);

    // Agrega una compuerta al tablero y marca su celda en la grilla
    void addGate(const Gate& gate);

    // Agrega un bloque al tablero y marca sus celdas en la grilla
    void addBlock(Block* block);

    // --- Logica del juego ---

    // Retorna el indice del bloque con ese id, o -1 si no existe
    int findBlock(int id) const;

    // Retorna true si el bloque puede moverse 'steps' celdas en 'dir'
    // dir: 'U'=arriba 'D'=abajo 'L'=izquierda 'R'=derecha
    // currentStep: paso actual (para verificar compuertas)
    bool canMove(int blockId, char dir, int steps, int currentStep) const;

    // Mueve el bloque 'steps' celdas en direccion 'dir'.
    // Actualiza la grilla (limpia celdas viejas, marca nuevas).
    // Retorna la cantidad real de celdas movidas.
    int moveBlock(int blockId, char dir, int steps, int currentStep);

    // Retorna true si el bloque puede salir por alguna salida en currentStep
    bool canExit(int blockId, int currentStep) const;

    // Elimina el bloque del tablero (salio por una salida).
    // Limpia sus celdas en la grilla.
    void removeBlock(int blockId);

    // Retorna true si todos los bloques salieron del tablero
    bool isGoal() const;

    // Visualizacion
    // Muestra el tablero en consola.
    // currentStep: paso actual (para mostrar colores de compuertas)
    void display(int currentStep = 0) const;

    // Marca las celdas de un bloque en la grilla como BLOCK_PART
    void placeBlock(Block* block);

    // Limpia las celdas de un bloque en la grilla (las pone EMPTY)
    void clearBlock(Block* block);

    // Retorna true si la celda (row,col) es transitable para un bloque
    // (vacia o compuerta del color correcto en ese paso)
    bool isFree(int row, int col, char blockColor, int currentStep) const;
};

#endif