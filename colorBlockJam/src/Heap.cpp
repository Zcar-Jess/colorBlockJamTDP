#include "Heap.h"
#include <iostream>

// Constructor
Heap::Heap(int cap) : size(0), capacity(cap) {
    // Indice basado en 1: arr[1] es la raiz, arr[0] no se usa
    arr = new GameState*[capacity + 1];
}

// Destructor
Heap::~Heap() {
    delete[] arr;  // NO libera los GameState, eso lo hace el Solver
}

// isEmpty
bool Heap::isEmpty() const {
    return size == 0;
}

// push: inserta un estado y reordena hacia arriba
void Heap::push(GameState* s) {
    if (size >= capacity) {
        // Duplicar capacidad si se llena
        capacity *= 2;
        GameState** newArr = new GameState*[capacity + 1];
        for (int i = 1; i <= size; i++) {
            newArr[i] = arr[i];
        }
        delete[] arr;
        arr = newArr;
    }
    arr[++size] = s;
    heapifyUp(size);
}

// pop: extrae la raiz (menor f) y reordena hacia abajo
GameState* Heap::pop() {
    if (isEmpty()) return nullptr;

    GameState* top = arr[1];    // guardar la raiz
    arr[1] = arr[size--];       // mover el ultimo a la raiz
    heapifyDown(1);             // reordenar hacia abajo
    return top;
}

// heapifyUp: sube arr[index] mientras su f sea menor que su padre
void Heap::heapifyUp(int index) {
    while (index > 1) {
        int parent = index / 2;
        if (arr[index]->f() < arr[parent]->f()) {
            // Intercambiar con el padre
            GameState* tmp = arr[index];
            arr[index]     = arr[parent];
            arr[parent]    = tmp;
            index = parent;
        } else {
            break;
        }
    }
}

// heapifyDown: baja arr[index] mientras algún hijo tenga menor f
void Heap::heapifyDown(int index) {
    while (2 * index <= size) {
        int child = 2 * index;  // hijo izquierdo

        // Elegir el hijo con menor f
        if (child + 1 <= size &&
            arr[child + 1]->f() < arr[child]->f()) {
            child++;  // hijo derecho es menor
        }

        if (arr[child]->f() < arr[index]->f()) {
            // Intercambiar con el hijo menor
            GameState* tmp = arr[index];
            arr[index]     = arr[child];
            arr[child]     = tmp;
            index = child;
        } else {
            break;
        }
    }
}

// print: muestra el heap (para debug)
void Heap::print() const {
    std::cout << "Heap[size=" << size << "]: ";
    for (int i = 1; i <= size; i++) {
        std::cout << "f=" << arr[i]->f() << " ";
    }
    std::cout << "\n";
}