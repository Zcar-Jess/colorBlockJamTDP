#include "Cell.h"
#include <iostream>
#include <cassert>

// testCell.cpp — prueba unitaria de la clase Cell
//
// Verifica que cada tipo de celda se configure correctamente
// y que se respete la restriccion:
// "una pared nunca puede ser simultaneamente salida y compuerta"
//
// Compilar desde raiz del proyecto:
//   make testCell

void testConstructorDefault() {
    std::cout << "[TEST] Constructor por defecto crea celda vacia...\n";

    Cell c;

    // Una celda nueva debe estar vacia y sin propiedades especiales
    assert(c.isEmpty()     == true);
    assert(c.isWall()      == false);
    assert(c.isBlockPart() == false);
    assert(c.isExit()      == false);
    assert(c.isGate()      == false);
    assert(c.refIndex == -1);
    assert(c.toChar()      == ' ');

    std::cout << "  PASSED\n";
}

void testSetAsWall() {
    std::cout << "[TEST] setAsWall() crea pared simple...\n";

    Cell c;
    c.setAsWall();

    // Debe ser pared pero sin propiedades de salida ni compuerta
    assert(c.isWall()      == true);
    assert(c.isExit()      == false);
    assert(c.isGate()      == false);
    assert(c.refIndex == -1);
    assert(c.toChar()      == '#');

    std::cout << "  PASSED\n";
}

void testSetAsExit() {
    std::cout << "[TEST] setAsExit() configura celda como salida...\n";

    Cell c;
    c.setAsExit(0); // salida con indice 0 en el Board

    // Una salida ES una pared (con propiedad de salida)
    assert(c.isWall()      == true);
    assert(c.isExit()      == true);
    assert(c.isGate()      == false); // nunca ambas
    assert(c.refIndex == 0);
    assert(c.toChar()      == 'E');

    std::cout << "  PASSED\n";
}

void testSetAsGate() {
    std::cout << "[TEST] setAsGate() configura celda como compuerta...\n";

    Cell c;
    c.setAsGate(2); // compuerta con indice 2 en el Board

    // Una compuerta ES una pared (con propiedad de compuerta)
    assert(c.isWall()      == true);
    assert(c.isGate()      == true);
    assert(c.isExit()      == false); // nunca ambas
    assert(c.refIndex == 2);
    assert(c.toChar()      == 'G');

    std::cout << "  PASSED\n";
}

void testMutualmenteExclusivos() {
    std::cout << "[TEST] Exit y Gate son mutuamente exclusivos (restriccion PDF)...\n";

    Cell c;

    // Primero configurar como exit
    c.setAsExit(0);
    assert(c.isExit() == true);
    assert(c.isGate() == false);

    // Luego como gate: debe desactivar exit automaticamente
    c.setAsGate(1);
    assert(c.isGate() == true);
    assert(c.isExit() == false); // se limpio solo

    // Luego como exit de nuevo: debe desactivar gate
    c.setAsExit(3);
    assert(c.isExit() == true);
    assert(c.isGate() == false); // se limpio solo

    std::cout << "  PASSED\n";
}

void testSetAsBlockPart() {
    std::cout << "[TEST] setAsBlockPart() marca celda como ocupada por bloque...\n";

    Cell c;
    c.setAsBlockPart();

    assert(c.isBlockPart() == true);
    assert(c.isExit()      == false);
    assert(c.isGate()      == false);
    assert(c.toChar()      == '*');

    std::cout << "  PASSED\n";
}

void testSetAsEmptyLimpia() {
    std::cout << "[TEST] setAsEmpty() limpia todas las propiedades...\n";

    Cell c;

    // Configurar con propiedades y luego vaciar
    c.setAsExit(0);
    c.setAsEmpty();

    // Debe quedar completamente limpia
    assert(c.isEmpty()     == true);
    assert(c.isExit()      == false);
    assert(c.isGate()      == false);
    assert(c.refIndex == -1);
    assert(c.toChar()      == ' ');

    std::cout << "  PASSED\n";
}

void testRefIndex() {
    std::cout << "[TEST] refIndex apunta al arreglo correcto del Board...\n";

    // Simula 3 salidas distintas en el Board
    Cell c0, c1, c2;
    c0.setAsExit(0);
    c1.setAsExit(1);
    c2.setAsGate(0); // primera compuerta (indice propio)

    assert(c0.refIndex == 0);
    assert(c1.refIndex == 1);
    assert(c2.refIndex == 0); // indice en gates[], no en exits[]

    std::cout << "  PASSED\n";
}

void testPrint() {
    std::cout << "[TEST] print() — salida visual:\n";
    Cell c;
    c.setAsExit(0);
    c.print();
    std::cout << "  (verificar visualmente)\n";
}

int main() {
    std::cout << "=== Tests de Cell ===\n";
    testConstructorDefault();
    testSetAsWall();
    testSetAsExit();
    testSetAsGate();
    testMutualmenteExclusivos();
    testSetAsBlockPart();
    testSetAsEmptyLimpia();
    testRefIndex();
    testPrint();
    std::cout << "\nTodos los tests de Cell pasaron OK.\n";
    return 0;
}