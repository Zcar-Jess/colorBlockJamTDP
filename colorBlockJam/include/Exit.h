#ifndef EXIT_H
#define EXIT_H

// Representa una salida del tablero.
// Las salidas estan en los bordes del tablero y tienen:
//   - Color constante
//   - Largo que puede variar con el tiempo (entre Li y Lf)
//   - Orientacion: H (horizontal) o V (vertical)


class Exit {
public:
    char color;       // Color de la salida (constante en el tiempo)
    int  x;           // Fila de la salida en el tablero
    int  y;           // Columna de la salida en el tablero
    char orientation; // 'H' = horizontal, 'V' = vertical
    int  li;          // Largo inicial
    int  lf;          // Largo final
    int  step;        // Cada cuantos pasos cambia el largo (0 = no cambia)

    // Constructor
    Exit();
    Exit(char color, int x, int y, char orientation, int li, int lf, int step);
 
    // Getters
    char getColor()       const;
    int  getX()           const;
    int  getY()           const;
    char getOrientation() const;
    int  getLi()          const;
    int  getLf()          const;
    int  getStep()        const;
 
    // Retorna el largo efectivo de la salida en el paso de tiempo t.
    // El largo oscila entre li y lf segun el paso.
    // Ejemplo: li=8, lf=5, step=1 → secuencia 8,7,6,5,6,7,8,7...
    // Si step==0, el largo no cambia (siempre retorna li).
    int getLengthAt(int t) const;
 
    // Retorna true si un bloque de ancho/alto 'blockSize' puede salir
    // por esta salida en el paso de tiempo t.
    // El bloque debe tener blockSize <= largo efectivo en ese instante.
    bool canFit(int blockSize, int t) const;
 
    // Muestra la salida por consola (para debug y tests)
    void print() const;
};
 
#endif
