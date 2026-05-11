#include "Gate.h"
#include <iostream>
#include <cassert>
 
// ------------------------------------------------------------
// testGate.cpp — prueba unitaria de la clase Gate
// Compilar desde raiz del proyecto:
//   make testGate
// ------------------------------------------------------------
 
void testGetters() {
    std::cout << "[TEST] Getters...\n";
 
    Gate g(3, 4, 'V', 2, 'a', 'c', 1);
 
    assert(g.getX()           == 3);
    assert(g.getY()           == 4);
    assert(g.getOrientation() == 'V');
    assert(g.getLi()          == 2);
    assert(g.getCi()          == 'a');
    assert(g.getCf()          == 'c');
    assert(g.getStep()        == 1);
 
    std::cout << "  PASSED\n";
}
 
void testColorConstante() {
    std::cout << "[TEST] Color constante (ci==cf o step==0)...\n";
 
    // ci == cf: siempre el mismo color
    Gate g1(0, 0, 'H', 1, 'b', 'b', 1);
    for (int t = 0; t < 10; t++) {
        assert(g1.getColorAt(t) == 'b');
    }
 
    // step == 0: color no cambia
    Gate g2(0, 0, 'H', 1, 'a', 'c', 0);
    for (int t = 0; t < 10; t++) {
        assert(g2.getColorAt(t) == 'a');
    }
 
    std::cout << "  PASSED\n";
}
 
void testColorCiclico() {
    std::cout << "[TEST] Color ciclico (ci='a', cf='c', step=1)...\n";
 
    // Ciclo: a, b, c, a, b, c, ...
    Gate g(0, 0, 'H', 2, 'a', 'c', 1);
 
    assert((char)g.getColorAt(0) == 'a');
    assert((char)g.getColorAt(1) == 'b');
    assert((char)g.getColorAt(2) == 'c');
    assert((char)g.getColorAt(3) == 'a');  // vuelve a ci
    assert((char)g.getColorAt(4) == 'b');
    assert((char)g.getColorAt(5) == 'c');
 
    std::cout << "  PASSED\n";
}
 
void testColorCiclicoStep2() {
    std::cout << "[TEST] Color ciclico con step=2...\n";
 
    // Cambia cada 2 pasos: ci='a', cf='b', step=2
    // t=0,1 → 'a'  | t=2,3 → 'b'  | t=4,5 → 'a' ...
    Gate g(0, 0, 'H', 1, 'a', 'b', 2);
 
    assert((char)g.getColorAt(0) == 'a');
    assert((char)g.getColorAt(1) == 'a');
    assert((char)g.getColorAt(2) == 'b');
    assert((char)g.getColorAt(3) == 'b');
    assert((char)g.getColorAt(4) == 'a');
 
    std::cout << "  PASSED\n";
}
 
void testCanPass() {
    std::cout << "[TEST] canPass()...\n";
 
    // Compuerta: ci='a', cf='c', step=1, largo=2
    Gate g(0, 0, 'H', 2, 'a', 'c', 1);
 
    // t=0: color='a' → bloque 'a' de ancho 2 puede pasar
    assert(g.canPass('a', 2, 0) == true);
 
    // t=0: color='a' → bloque 'b' NO puede pasar (distinto color)
    assert(g.canPass('b', 1, 0) == false);
 
    // t=1: color='b' → bloque 'b' de ancho 1 puede pasar
    assert(g.canPass('b', 1, 1) == true);
 
    // t=1: color='b' → bloque 'b' de ancho 3 NO puede pasar (muy grande)
    assert(g.canPass('b', 3, 1) == false);
 
    // t=2: color='c' → bloque 'c' de ancho 2 puede pasar
    assert(g.canPass('c', 2, 2) == true);
 
    // t=3: vuelve a 'a'
    assert(g.canPass('a', 1, 3) == true);
 
    std::cout << "  PASSED\n";
}
 
void testPrint() {
    std::cout << "[TEST] print() — salida visual:\n";
    Gate g(3, 4, 'V', 2, 'a', 'c', 1);
    g.print();
    std::cout << "  (verificar visualmente)\n";
}
 
int main() {
    std::cout << "=== Tests de Gate ===\n";
    testGetters();
    testColorConstante();
    testColorCiclico();
    testColorCiclicoStep2();
    testCanPass();
    testPrint();
    std::cout << "\nTodos los tests de Gate pasaron OK.\n";
    return 0;
}
