#include "Cell.h"
#include <iostream>


// Constructor por defecto
// Una celda nueva comienza vacia y sin propiedades especiales
Cell::Cell()
    : type(EMPTY), isExitFlag(false), isGateFlag(false), refIndex(-1)
{}

// Constructor con parametros
// Permite crear una celda con un estado especifico de una vez,
Cell::Cell(Type t, bool isExit, bool isGate, int ref)
    : type(t), isExitFlag(isExit), isGateFlag(isGate), refIndex(ref)
{}

// Getters
// Consultas simples sobre el estado de la celda
Cell::Type Cell::getType()     const { return type; }
bool       Cell::isEmpty()     const { return type == EMPTY; }
bool       Cell::isWall()      const { return type == WALL; }
bool       Cell::isBlockPart() const { return type == BLOCK_PART; }
bool Cell::isExit()      const { return isExitFlag; }
bool Cell::isGate()      const { return isGateFlag; }

// setAsExit: convierte la celda en una salida del tablero.
// Se fuerza isGateFlag=false para respetar la restriccion.
// index: posicion en el arreglo exits[] del Board
void Cell::setAsExit(int index) {
    type       = WALL;
    isExitFlag = true;
    isGateFlag = false; // RESTRICCION: nunca ambas true
    refIndex   = index;
}

// setAsGate: convierte la celda en una compuerta.
// Las compuertas tambien son paredes internas del tablero.
// Se fuerza isExitFlag=false para respetar la restriccion.
// index: posicion en el arreglo gates[] del Board
void Cell::setAsGate(int index) {
    type       = WALL;
    isExitFlag = false; // RESTRICCION: nunca ambas true
    isGateFlag = true;
    refIndex   = index;
}

// setAsWall: pared simple, sin salida ni compuerta.
// Resetea todas las propiedades especiales.
void Cell::setAsWall() {
    type       = WALL;
    isExitFlag = false;
    isGateFlag = false;
    refIndex   = -1;
}

// setAsEmpty: celda vacia, un bloque puede moverse por aqui.
// Limpia todas las propiedades (una celda vacia no puede ser
// salida ni compuerta).
void Cell::setAsEmpty() {
    type       = EMPTY;
    isExitFlag = false;
    isGateFlag = false;
    refIndex   = -1;
}

// setAsBlockPart: la celda esta ocupada por parte de un bloque.
// El Board sabe que bloque la ocupa; la celda solo registra
// que esta ocupada para verificar colisiones rapidamente.
void Cell::setAsBlockPart() {
    type       = BLOCK_PART;
    isExitFlag = false;
    isGateFlag = false;
    refIndex   = -1;
}

// toChar: caracter visual para imprimir el tablero.
// El Board reemplaza '*' por la letra del color del bloque
// cuando muestra el tablero completo.
char Cell::toChar() const {
    if (isExitFlag) return 'E'; // salida
    if (isGateFlag) return 'G'; // compuerta
    switch (type) {
        case WALL:       return '#';
        case EMPTY:      return ' ';
        case BLOCK_PART: return '*'; // el Board pone el color real
        default:         return '?';
    }
}

// print: muestra todos los datos de la celda (para debug)
void Cell::print() const {
    std::cout << "Cell[" << toChar() << "]"
              << " type="   << type
              << " isExit=" << isExitFlag
              << " isGate=" << isGateFlag
              << " ref="    << refIndex << "\n";
}