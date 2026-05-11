#include "Block.h"
#include <iostream>
#include <cassert>

// testBlock.cpp  — prueba unitaria de la clase Block
// aqui verificamos que Block se construye, copia y compara bien.

void testConstructorYGetters() {
    std::cout << "[TEST] Constructor y getters...\n";

    // Bloque 2x2 totalmente relleno
    bool geom[] = {1, 1, 1, 1};
    Block b(1, 'a', 2, 2, 4, 4, 0, geom);

    assert(b.getId()        == 1);
    assert(b.getColor()     == 'a');
    assert(b.getWidth()     == 2);
    assert(b.getHeight()    == 2);
    assert(b.getX()         == 4);
    assert(b.getY()         == 4);
    assert(b.getColorLock() == 0);

    // Todas las celdas deben estar activas
    assert(b.cellActive(0, 0) == true);
    assert(b.cellActive(0, 1) == true);
    assert(b.cellActive(1, 0) == true);
    assert(b.cellActive(1, 1) == true);

    // Fuera del bounding box: siempre false
    assert(b.cellActive(-1, 0) == false);
    assert(b.cellActive(2,  0) == false);

    std::cout << "  PASSED\n";
}

void testGeometriaIrregular() {
    std::cout << "[TEST] Geometria en L (3x2)...\n";

    // Forma en L:
    //  # .
    //  # .
    //  # #
    bool geom[] = {
        1,  0,
        1,  0,
        1,  1
    };
    Block b(2, 'b', 2, 3, 0, 0, 0, geom);

    assert(b.cellActive(0, 0) == true);
    assert(b.cellActive(0, 1) == false);
    assert(b.cellActive(1, 0) == true);
    assert(b.cellActive(1, 1) == false);
    assert(b.cellActive(2, 0) == true);
    assert(b.cellActive(2, 1) == true);

    std::cout << "  PASSED\n";
}

void testConstructorCopia() {
    std::cout << "[TEST] Constructor de copia (independencia de memoria)...\n";

    bool geom[] = {true, true, true, true};
    Block original(1, 'a', 2, 2, 0, 0, 0, geom);
    Block copia(original);

    // La copia debe ser igual
    assert(copia.equals(original));

    // Mover la copia NO debe afectar al original
    copia.setX(5);
    copia.setY(5);
    assert(original.getX() == 0);
    assert(original.getY() == 0);
    assert(copia.getX()    == 5);

    std::cout << "  PASSED\n";
}

void testEquals() {
    std::cout << "[TEST] equals()...\n";

    bool geom[] = {true, false, true, true};
    Block b1(3, 'c', 2, 2, 1, 2, 0, geom);
    Block b2(b1);  // copia exacta

    assert(b1.equals(b2));

    // Distinta posicion → no son iguales
    b2.setX(9);
    assert(!b1.equals(b2));

    std::cout << "  PASSED\n";
}

void testColorLock() {
    std::cout << "[TEST] colorLock...\n";

    bool geom[] = {true};
    Block b(4, 'd', 1, 1, 0, 0, 3, geom);

    assert(b.getColorLock() == 3);
    b.decrementLock();
    assert(b.getColorLock() == 2);
    b.decrementLock();
    b.decrementLock();
    assert(b.getColorLock() == 0);
    b.decrementLock();  // no debe bajar de 0
    assert(b.getColorLock() == 0);

    std::cout << "  PASSED\n";
}

void testPrint() {
    std::cout << "[TEST] print() — salida visual:\n";
    bool geom[] = {true, true, true, true};
    Block b(1, 'a', 2, 2, 4, 4, 0, geom);
    b.print();
    std::cout << "  (verificar visualmente)\n";
}

int main() {
    std::cout << "=== Tests de Block ===\n";
    testConstructorYGetters();
    testGeometriaIrregular();
    testConstructorCopia();
    testEquals();
    testColorLock();
    testPrint();
    std::cout << "\nTodos los tests de Block pasaron OK.\n";
    return 0;
}