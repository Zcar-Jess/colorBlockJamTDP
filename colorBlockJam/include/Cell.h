#ifndef CELL_H
#define CELL_H

// Cell: representa una casilla individual del tablero.
//
// El tablero es una matriz de H x W celdas. Cada posicion (i,j)
// es una Cell.
//
//   EMPTY      → fondo del tablero, los bloques se mueven por aqui
//   WALL       → pared, ningun bloque puede pasar
//   BLOCK_PART → parte de un bloque
//
// Ademas, una celda WALL puede tener una propiedad especial:
//   - isExitFlag: es una salida del tablero
//   - isGateFlag: es una compuerta interna
//
// Restriccion: una pared NUNCA puede ser simultaneamente
// salida y compuerta. isExitFlag e isGateFlag son mutuamente exclusivos.
//
// refIndex guarda el indice dentro del arreglo de exits[] o gates[]
// del Board para acceder a sus datos rapidamente. Vale -1 si no aplica.

class Cell {
public:
    // Tipos posibles de una celda
    enum Type {
        EMPTY,      // casilla libre, los bloques pueden moverse aqui
        WALL,       // pared fija, bloquea el movimiento
        BLOCK_PART  // ocupada por parte de un bloque movil
    };
    Type type;        // tipo principal de la celda, asegura que solo pueda ser una
    bool isExitFlag;  // true: esta celda es una salida del tablero
                      // solo puede ser true si type == WALL

    bool isGateFlag;  // true: esta celda es una compuerta
                      // solo puede ser true si type == WALL
                      // NUNCA true al mismo tiempo que isExitFlag

    int  refIndex;    // indice en exits[] o gates[] del Board
                      // vale -1 si no es salida ni compuerta

    // Constructores
    Cell();
    Cell(Type type, bool isExitFlag, bool isGateFlag, int refIndex);

    // Metodos
    bool isEmpty()     const; // true si type == EMPTY
    bool isWall()      const; // true si type == WALL
    bool isBlockPart() const; // true si type == BLOCK_PART
    bool isExit()      const; // true si isExitFlag == true
    bool isGate()      const; // true si isGateFlag == true
    Cell::Type getType()     const; // devuelve el tipo de la celda
    
    // Setters
    // Cada uno garantiza que isExitFlag e isGateFlag
    // nunca queden ambos en true al mismo tiempo
    void setAsExit(int index);   // WALL + isExitFlag=true
    void setAsGate(int index);   // WALL + isGateFlag=true
    void setAsWall();            // WALL sin propiedades especiales
    void setAsEmpty();           // celda vacia, limpia todo
    void setAsBlockPart();       // ocupada por un bloque

    // Caracter visual: 'E'=salida 'G'=compuerta '#'=pared ' '=vacio '*'=bloque
    char toChar() const;

    // Muestra informacion de la celda por consola
    void print() const;
};

#endif