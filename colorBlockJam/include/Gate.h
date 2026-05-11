#ifndef GATE_H
#define GATE_H
 
// Representa una compuerta en el tablero Color Block Jam.
// Las compuertas son paredes internas que cambian de color ciclicamente.
// Un bloque puede atravesarla si su color coincide y tiene el ancho/alto correcto.
// A diferencia de las salidas, las compuertas NO estan en el borde del tablero.
 
class Gate {
public:
    int  x;           // Fila de la compuerta en el tablero
    int  y;           // Columna de la compuerta en el tablero
    char orientation; // 'H' = horizontal, 'V' = vertical
    int  li;          // Largo de la compuerta
    int  ci;          // Color inicial (en ascii: 'a'=97, 'b'=98, ...)
    int  cf;          // Color final del ciclo (vuelve a ci despues)
    int  step;        // Cada cuantos pasos cambia el color (0 = no cambia)

    // Constructor
    Gate();
    Gate(int x, int y, char orientation, int li, int ci, int cf, int step);
 
    // --- Getters ---
    int  getX()           const;
    int  getY()           const;
    char getOrientation() const;
    int  getLi()          const;
    int  getCi()          const;
    int  getCf()          const;
    int  getStep()        const;
 
    // Retorna el color actual de la compuerta en el paso de tiempo t.
    // El color avanza de ci a cf y luego vuelve a ci.
    // Si step==0, el color no cambia (siempre retorna ci).
    // Ejemplo: ci='a', cf='c', step=1 → a, b, c, a, b, c, ...
    int getColorAt(int t) const;
 
    // Retorna true si un bloque puede atravesar la compuerta en el paso t:
    //   - El color del bloque coincide con el color actual de la compuerta
    //   - El tamanio del bloque (ancho o alto segun orientacion) cabe en li
    bool canPass(char blockColor, int blockSize, int t) const;
 
    // Muestra la compuerta por consola (para debug y tests)
    void print() const;
};
 
#endif
 
