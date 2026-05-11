#include "Exit.h"
#include <iostream>

// Constructor
Exit::Exit()
    : color(' '), x(0), y(0), orientation('H'),
      li(0), lf(0), step(0)
{}
Exit::Exit(char color, int x, int y, char orientation,
           int li, int lf, int step)
    : color(color), x(x), y(y), orientation(orientation),
      li(li), lf(lf), step(step)
{}

// Getters
char Exit::getColor()       const { return color; }
int  Exit::getX()           const { return x; }
int  Exit::getY()           const { return y; }
char Exit::getOrientation() const { return orientation; }
int  Exit::getLi()          const { return li; }
int  Exit::getLf()          const { return lf; }
int  Exit::getStep()        const { return step; }

// getLengthAt(t): calcula el largo efectivo en el paso t.
//
// El largo oscila entre li y lf. Las celdas se apagan desde
// la de mayor coordenada hacia la menor.
//
// Ejemplo del PDF: li=8, lf=5, step=1
//   t=0 → 8, t=1 → 7, t=2 → 6, t=3 → 5,
//   t=4 → 6, t=5 → 7, t=6 → 8, t=7 → 7 ...
//
// Si step==0 el largo no cambia: siempre retorna li.
int Exit::getLengthAt(int t) const {
    if (step == 0) return li;
 
    int range = li - lf;          // cuanto varia (puede ser 0)
    if (range == 0) return li;    // li == lf, no cambia
 
    // periodo completo: baja de li a lf y sube de lf a li
    // periodo = range * 2 pasos
    int period = range * 2;
 
    // cuantos ticks han pasado
    int ticks = t / step;
 
    // posicion dentro del periodo
    int pos = ticks % period;
 
    if (pos <= range) {
        return li - pos;          // bajando: li → lf
    } else {
        return lf + (pos - range); // subiendo: lf → li
    }
}

// canFit: retorna true si el bloque cabe en la salida en paso t.
// El bloque debe tener blockSize <= largo efectivo.
bool Exit::canFit(int blockSize, int t) const {
    return blockSize <= getLengthAt(t);
}
 

// print: muestra la salida (para test)
void Exit::print() const {
    std::cout << "Exit color='" << color
              << "' pos=(" << x << "," << y << ")"
              << " orient=" << orientation
              << " li=" << li << " lf=" << lf
              << " step=" << step << "\n";
}
 
