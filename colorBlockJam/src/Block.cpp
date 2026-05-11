#include "Block.h"
#include <iostream>

// ------------------------------------------------------------
// Constructor principal
// ------------------------------------------------------------
Block::Block(int id, char color, int width, int height,
             int x, int y, int colorLock, const bool* geom)
    : id(id), color(color), width(width), height(height),
      x(x), y(y), colorLock(colorLock)
{
    int size = width * height;
    geometry = new bool[size];
    for (int i = 0; i < size; i++) {
        geometry[i] = geom[i];
    }
}

// ------------------------------------------------------------
// Constructor de copia
// Necesario porque A* duplica estados para explorar ramas
// (igual que en el ejemplo de envases, donde el State se copia
//  al generar vecinos)
// ------------------------------------------------------------
Block::Block(const Block& other)
    : id(other.id), color(other.color),
      width(other.width), height(other.height),
      x(other.x), y(other.y), colorLock(other.colorLock)
{
    int size = width * height;
    geometry = new bool[size];
    for (int i = 0; i < size; i++) {
        geometry[i] = other.geometry[i];
    }
}

// ------------------------------------------------------------
// Operador de asignacion
// ------------------------------------------------------------
Block& Block::operator=(const Block& other) {
    if (this == &other) return *this;

    delete[] geometry;

    id        = other.id;
    color     = other.color;
    width     = other.width;
    height    = other.height;
    x         = other.x;
    y         = other.y;
    colorLock = other.colorLock;

    int size = width * height;
    geometry = new bool[size];
    for (int i = 0; i < size; i++) {
        geometry[i] = other.geometry[i];
    }
    return *this;
}

// ------------------------------------------------------------
// Destructor
// ------------------------------------------------------------
Block::~Block() {
    delete[] geometry;
}

// ------------------------------------------------------------
// Getters
// ------------------------------------------------------------
int   Block::getId()        const { return id; }
char  Block::getColor()     const { return color; }
int   Block::getWidth()     const { return width; }
int   Block::getHeight()    const { return height; }
int   Block::getX()         const { return x; }
int   Block::getY()         const { return y; }
int   Block::getColorLock() const { return colorLock; }

// ------------------------------------------------------------
// Retorna true si la celda local (row, col) forma parte del bloque.
// La geometria se almacena en fila mayor: indice = row*width + col
// ------------------------------------------------------------
bool Block::cellActive(int row, int col) const {
    if (row < 0 || row >= height || col < 0 || col >= width)
        return false;
    return geometry[row * width + col];
}

// ------------------------------------------------------------
// Setters de posicion
// ------------------------------------------------------------
void Block::setX(int newX) { x = newX; }
void Block::setY(int newY) { y = newY; }

// ------------------------------------------------------------
// Decrementa el bloqueo de color
// ------------------------------------------------------------
void Block::decrementLock() {
    if (colorLock > 0) colorLock--;
}

// ------------------------------------------------------------
// Compara este bloque con otro.
// Dos bloques son iguales si tienen el mismo id, posicion y geometria.
// Usado por GameState::equals() para comparar estados en el ClosedSet.
// ------------------------------------------------------------
bool Block::equals(const Block& other) const {
    if (id != other.id || x != other.x || y != other.y) return false;
    if (width != other.width || height != other.height)  return false;
    int size = width * height;
    for (int i = 0; i < size; i++) {
        if (geometry[i] != other.geometry[i]) return false;
    }
    return true;
}

// ------------------------------------------------------------
// Imprime el bloque (util para testear y visualizar)
// ------------------------------------------------------------
void Block::print() const {
    std::cout << "Block[" << id << "] color='" << color
              << "' pos=(" << x << "," << y << ")"
              << " size=" << width << "x" << height
              << " lock=" << colorLock << "\n";
    std::cout << "Geometry:\n";
    for (int r = 0; r < height; r++) {
        std::cout << "  ";
        for (int c = 0; c < width; c++) {
            std::cout << (geometry[r * width + c] ? color : '.');
        }
        std::cout << "\n";
    }
}