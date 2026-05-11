#include "Gate.h"
#include <iostream>

// Constructor
Gate::Gate()
    : x(0), y(0), orientation('H'),
      li(0), ci('a'), cf('a'), step(0)
{}
Gate::Gate(int x, int y, char orientation, int li, int ci, int cf, int step)
    : x(x), y(y), orientation(orientation), li(li), ci(ci), cf(cf), step(step) {}

// Getters
int Gate::getX()            const { return x; }
int Gate::getY()            const { return y; }
char Gate::getOrientation() const { return orientation; }
int Gate::getLi()           const { return li; }
int Gate::getCi()           const { return ci; }
int Gate::getCf()           const { return cf; }
int Gate::getStep()         const { return step; }

// getColorAt(t): retorna el color de la compuerta en el paso t.
// El color cicla desde ci hasta cf y luego vuelve a ci.
// Ejemplo PDF: ci='a'(97), cf='c'(99), step=1
//   t=0 → 'a', t=1 → 'b', t=2 → 'c', t=3 → 'a', t=4 → 'b'
//
// Si ci == cf el color no cambia (aunque step != 0).
// Si step == 0 el color tampoco cambia.
int Gate::getColorAt(int t) const {
    if (step == 0 || ci == cf) return ci;
 
    int range  = cf - ci + 1;   // cantidad de colores en el ciclo
    int ticks  = t / step;      // cuantos cambios han ocurrido
    return ci + (ticks % range);
}
 
// canPass: retorna true si el bloque puede atravesar la compuerta.
//   1. El color del bloque debe coincidir con el color actual.
//   2. El tamanio del bloque debe ser <= largo de la compuerta.
bool Gate::canPass(char blockColor, int blockSize, int t) const {
    bool colorMatch = (blockColor == (char)getColorAt(t));
    bool sizeMatch  = (blockSize <= li);
    return colorMatch && sizeMatch;
}
 
// print: muestra la compuerta (para test)
void Gate::print() const {
    std::cout << "Gate pos=(" << x << "," << y << ")"
              << " orient=" << orientation
              << " li=" << li
              << " ci=" << (char)ci << " cf=" << (char)cf
              << " step=" << step << "\n";
}
 
