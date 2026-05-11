#include "Exit.h"
#include <iostream>
#include <cassert>
 
// testExit.cpp — prueba unitaria de la clase Exit
// Compilar desde raiz del proyecto:
//   g++ -o testExit test_class/testExit.cpp src/Exit.cpp -I include/
void testGetters() {
    std::cout << "[TEST] Getters...\n";
 
    Exit e('a', 4, 7, 'V', 2, 2, 0);
 
    assert(e.getColor()       == 'a');
    assert(e.getX()           == 4);
    assert(e.getY()           == 7);
    assert(e.getOrientation() == 'V');
    assert(e.getLi()          == 2);
    assert(e.getLf()          == 2);
    assert(e.getStep()        == 0);
 
    std::cout << "  PASSED\n";
}
 
void testLargoConstante() {
    std::cout << "[TEST] Largo constante (step=0 o li==lf)...\n";
 
    // Caso del ejemplo del PDF: EXIT li=2 lf=2 step=0
    Exit e('a', 4, 7, 'V', 2, 2, 0);
 
    // En cualquier paso, el largo debe ser siempre 2
    for (int t = 0; t < 20; t++) {
        assert(e.getLengthAt(t) == 2);
    }
 
    std::cout << "  PASSED\n";
}
 
void testLargoOscilante() {
    std::cout << "[TEST] Largo oscilante (li=8, lf=5, step=1)...\n";
 
    // Ejemplo exacto del PDF: secuencia 8,7,6,5,6,7,8,7...
    Exit e('b', 0, 3, 'H', 8, 5, 1);
 
    int esperado[] = {8, 7, 6, 5, 6, 7, 8, 7, 6, 5, 6, 7, 8};
    int n = sizeof(esperado) / sizeof(int);
 
    for (int t = 0; t < n; t++) {
        int largo = e.getLengthAt(t);
        if (largo != esperado[t]) {
            std::cout << "  FALLO en t=" << t
                      << " esperado=" << esperado[t]
                      << " obtenido=" << largo << "\n";
            assert(false);
        }
    }
 
    std::cout << "  PASSED\n";
}
 
void testLargoOscilanteStep2() {
    std::cout << "[TEST] Largo oscilante con step=2...\n";
 
    // li=6, lf=4, step=2 → cambia cada 2 pasos
    // t=0,1 → 6  | t=2,3 → 5  | t=4,5 → 4  | t=6,7 → 5  | t=8,9 → 6
    Exit e('c', 0, 0, 'H', 6, 4, 2);
 
    assert(e.getLengthAt(0) == 6);
    assert(e.getLengthAt(1) == 6);
    assert(e.getLengthAt(2) == 5);
    assert(e.getLengthAt(3) == 5);
    assert(e.getLengthAt(4) == 4);
    assert(e.getLengthAt(5) == 4);
    assert(e.getLengthAt(6) == 5);
    assert(e.getLengthAt(7) == 5);
    assert(e.getLengthAt(8) == 6);
 
    std::cout << "  PASSED\n";
}
 
void testCanFit() {
    std::cout << "[TEST] canFit()...\n";
 
    // Salida fija de largo 2 (ejemplo del PDF)
    Exit e('a', 4, 7, 'V', 2, 2, 0);
 
    // Bloque de ancho 2 cabe (2 <= 2)
    assert(e.canFit(2, 0) == true);
 
    // Bloque de ancho 1 cabe (1 <= 2)
    assert(e.canFit(1, 0) == true);
 
    // Bloque de ancho 3 NO cabe (3 > 2)
    assert(e.canFit(3, 0) == false);
 
    // Con largo oscilante: li=8, lf=5, step=1
    Exit e2('b', 0, 0, 'H', 8, 5, 1);
 
    // En t=3 el largo es 5
    assert(e2.canFit(5, 3) == true);
    assert(e2.canFit(6, 3) == false);
 
    // En t=0 el largo es 8
    assert(e2.canFit(8, 0) == true);
    assert(e2.canFit(9, 0) == false);
 
    std::cout << "  PASSED\n";
}
 
void testPrint() {
    std::cout << "[TEST] print() — salida visual:\n";
    Exit e('a', 4, 7, 'V', 2, 2, 0);
    e.print();
    std::cout << "  (verificar visualmente)\n";
}
 
int main() {
    std::cout << "=== Tests de Exit ===\n";
    testGetters();
    testLargoConstante();
    testLargoOscilante();
    testLargoOscilanteStep2();
    testCanFit();
    testPrint();
    std::cout << "\nTodos los tests de Exit pasaron OK.\n";
    return 0;
}
 
