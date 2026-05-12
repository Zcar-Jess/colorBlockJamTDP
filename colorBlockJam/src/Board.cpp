#include "Board.h"
#include <iostream>
#include <cstring>

// Constructor
Board::Board(const char* n, int w, int h, int sl,
             int maxB, int maxE, int maxG)
    : width(w), height(h), stepLimit(sl),
      numBlocks(0), maxBlocks(maxB),
      numExits(0),  maxExits(maxE),
      numGates(0),  maxGates(maxG)
{
    strncpy(name, n, 63);
    name[63] = '\0';

    // Crear grilla height x width, todas las celdas vacias
    grid = new Cell*[height];
    for (int i = 0; i < height; i++) {
        grid[i] = new Cell[width];
    }

    // Crear arreglos de bloques, salidas y compuertas
    blocks = new Block*[maxBlocks];
    exits  = new Exit[maxExits];
    gates  = new Gate[maxGates];
}

// Constructor de copia (clona el tablero completo para A*)
Board::Board(const Board& other)
    : width(other.width), height(other.height),
      stepLimit(other.stepLimit),
      numBlocks(other.numBlocks), maxBlocks(other.maxBlocks),
      numExits(other.numExits),   maxExits(other.maxExits),
      numGates(other.numGates),   maxGates(other.maxGates)
{
    strncpy(name, other.name, 63);
    name[63] = '\0';

    // Clonar grilla
    grid = new Cell*[height];
    for (int i = 0; i < height; i++) {
        grid[i] = new Cell[width];
        for (int j = 0; j < width; j++) {
            grid[i][j] = other.grid[i][j];
        }
    }

    // Clonar bloques (copia profunda)
    blocks = new Block*[maxBlocks];
    for (int i = 0; i < numBlocks; i++) {
        blocks[i] = new Block(*other.blocks[i]);
    }

    // Clonar salidas y compuertas (copia directa, son datos fijos)
    exits = new Exit[maxExits];
    for (int i = 0; i < numExits; i++) {
        exits[i] = other.exits[i];
    }

    gates = new Gate[maxGates];
    for (int i = 0; i < numGates; i++) {
        gates[i] = other.gates[i];
    }
}

// Destructor
Board::~Board() {
    // Liberar grilla
    for (int i = 0; i < height; i++) {
        delete[] grid[i];
    }
    delete[] grid;

    // Liberar bloques
    for (int i = 0; i < numBlocks; i++) {
        delete blocks[i];
    }
    delete[] blocks;

    delete[] exits;
    delete[] gates;
}

// Configuracion del tablero
void Board::setWall(int row, int col) {
    grid[row][col].setAsWall();
}

void Board::addExit(const Exit& e) {

    exits[numExits] = e;

    int idx = numExits;

    numExits++;

    // marcar en la grilla

    if (e.orientation == 'H') {

        for (int k = 0; k < e.li; k++) {

            grid[e.x][e.y + k]
                .setAsExit(idx);
        }

    } else {

        for (int k = 0; k < e.li; k++) {

            grid[e.x + k][e.y]
                .setAsExit(idx);
        }
    }
}

void Board::addGate(const Gate& gate) {
    gates[numGates] = gate;
    grid[gate.x][gate.y].setAsGate(numGates);
    numGates++;
}

void Board::addBlock(Block* block) {
    // Validar que el bloque esta dentro del tablero
    if (block->x < 0 || block->x + block->height > height ||
        block->y < 0 || block->y + block->width  > width) {
        // Bloque fuera de rango: ignorar silenciosamente
        delete block;
        return;
    }
    blocks[numBlocks++] = block;
    placeBlock(block);
}

// Marca las celdas del bloque en la grilla como BLOCK_PART
void Board::placeBlock(Block* block) {
    for (int r = 0; r < block->height; r++) {
        for (int c = 0; c < block->width; c++) {
            if (block->cellActive(r, c)) {
                int row = block->x + r;
                int col = block->y + c;
                grid[row][col].setAsBlockPart();
            }
        }
    }
}

// Limpia las celdas del bloque en la grilla (EMPTY)
void Board::clearBlock(Block* block) {
    for (int r = 0; r < block->height; r++) {
        for (int c = 0; c < block->width; c++) {
            if (block->cellActive(r, c)) {
                int row = block->x + r;
                int col = block->y + c;
                grid[row][col].setAsEmpty();
            }
        }
    }
}

// findBlock: retorna el indice del bloque con ese id, o -1
int Board::findBlock(int id) const {
    for (int i = 0; i < numBlocks; i++) {
        if (blocks[i]->id == id) return i;
    }
    return -1;
}

// isFree: retorna true si la celda (row,col) es transitable.
// Una celda es transitable si es EMPTY o si es una compuerta
// del color correcto en el paso actual.
bool Board::isFree(int row, int col, char blockColor, int currentStep) const {
    if (row < 0 || row >= height || col < 0 || col >= width)
        return false;

    Cell& cell = grid[row][col];

    if (cell.isEmpty()) return true;

    // Compuerta: transitable si el color coincide
    if (cell.isGate()) {
        Gate& g = gates[cell.refIndex];
        return g.canPass(blockColor, 1, currentStep);
    }

    return false;
}

// canMove: verifica si el bloque puede moverse 'steps' celdas
// en la direccion 'dir' sin colisionar con paredes u otros bloques.
bool Board::canMove(int blockId, char dir, int steps, int currentStep) const {
    int idx = findBlock(blockId);
    if (idx == -1 || steps <= 0) return false;

    Block* b = blocks[idx];

    // Determinar delta de movimiento
    int dr = 0, dc = 0;
    if      (dir == 'U') dr = -1;
    else if (dir == 'D') dr =  1;
    else if (dir == 'L') dc = -1;
    else if (dir == 'R') dc =  1;
    else return false;

    // Verificar celda por celda en la direccion del movimiento
    for (int step = 1; step <= steps; step++) {
        for (int r = 0; r < b->height; r++) {
            for (int c = 0; c < b->width; c++) {
                if (!b->cellActive(r, c)) continue;

                int newRow = b->x + r + dr * step;
                int newCol = b->y + c + dc * step;

                // La celda destino debe estar libre
                // (ignoramos celdas del mismo bloque)
                if (!isFree(newRow, newCol, b->color, currentStep)) {
                    // Verificar que no sea parte del mismo bloque
                    bool ownCell = false;
                    for (int r2 = 0; r2 < b->height && !ownCell; r2++) {
                        for (int c2 = 0; c2 < b->width && !ownCell; c2++) {
                            if (b->cellActive(r2, c2) &&
                                b->x + r2 == newRow &&
                                b->y + c2 == newCol) {
                                ownCell = true;
                            }
                        }
                    }
                    if (!ownCell) return false;
                }
            }
        }
    }
    return true;
}

// moveBlock: mueve el bloque y actualiza la grilla.
// Retorna la cantidad de celdas movidas.
int Board::moveBlock(int blockId, char dir, int steps, int currentStep) {
    int idx = findBlock(blockId);
    if (idx == -1) return 0;

    Block* b = blocks[idx];
    int dr = 0, dc = 0;
    if      (dir == 'U') dr = -1;
    else if (dir == 'D') dr =  1;
    else if (dir == 'L') dc = -1;
    else if (dir == 'R') dc =  1;

    // Encontrar cuantos pasos realmente puede moverse
    int actualSteps = 0;
    for (int step = 1; step <= steps; step++) {
        if (canMove(blockId, dir, step, currentStep)) {
            actualSteps = step;
        } else {
            break;
        }
    }

    if (actualSteps == 0) return 0;

    // Limpiar posicion actual en la grilla
    clearBlock(b);

    // Actualizar posicion del bloque
    b->x += dr * actualSteps;
    b->y += dc * actualSteps;

    // Marcar nueva posicion en la grilla
    placeBlock(b);

    return actualSteps;
}

// canExit: verifica si el bloque puede salir por alguna salida.
// Condiciones:
//   El bloque esta adyacente a la salida (no hay celdas entre ambos)
//   El color del bloque coincide con el color de la salida
//   El ancho o alto del bloque es <= largo efectivo de la salida
bool Board::canExit(int blockId, int currentStep) const {
    int idx = findBlock(blockId);
    if (idx == -1) return false;

    Block* b = blocks[idx];

    for (int e = 0; e < numExits; e++) {
        Exit& ex = exits[e];

        // 1. Color debe coincidir
        if (ex.color != b->color) continue;

        int L = ex.getLengthAt(currentStep);

        // 2. Salida VERTICAL: ocupa filas ex.x..ex.x+L-1 en columna ex.y
        if (ex.orientation == 'V') {

            // El bloque debe caber en altura
            if (!ex.canFit(b->height, currentStep)) continue;

            // El bloque debe estar alineado dentro del rango de filas de la salida
            if (b->x < ex.x || b->x + b->height > ex.x + L) continue;

            // Borde izquierdo: bloque adyacente a columna 0
            if (ex.y == 0 && b->y == 1) return true;

            // Borde derecho: bloque adyacente a columna width-1
            if (ex.y == width - 1 && b->y + b->width == width - 1) return true;
        }

        // 3. Salida HORIZONTAL: ocupa columnas ex.y..ex.y+L-1 en fila ex.x
        else if (ex.orientation == 'H') {

            // El bloque debe caber en ancho
            if (!ex.canFit(b->width, currentStep)) continue;

            // El bloque debe estar alineado dentro del rango de columnas de la salida
            if (b->y < ex.y || b->y + b->width > ex.y + L) continue;

            // Borde superior: bloque adyacente a fila 0
            if (ex.x == 0 && b->x == 1) return true;

            // Borde inferior: bloque adyacente a fila height-1
            if (ex.x == height - 1 && b->x + b->height == height - 1) return true;
        }
    }
    return false;
}
// removeBlock: elimina el bloque del tablero (salio).
// Limpia sus celdas y lo quita del arreglo.
void Board::removeBlock(int blockId) {
    int idx = findBlock(blockId);
    if (idx == -1) return;

    clearBlock(blocks[idx]);
    delete blocks[idx];

    // Compactar el arreglo
    for (int i = idx; i < numBlocks - 1; i++) {
        blocks[i] = blocks[i + 1];
    }
    numBlocks--;
}

// isGoal: retorna true si todos los bloques salieron
bool Board::isGoal() const {
    return numBlocks == 0;
}

// display: muestra el tablero en consola
// Los bloques se muestran con su letra de color
void Board::display(int currentStep) const {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            Cell& cell = grid[i][j];

            if (cell.isBlockPart()) {
                // Buscar que bloque ocupa esta celda
                char c = '?';
                for (int b = 0; b < numBlocks; b++) {
                    Block* blk = blocks[b];
                    int localR = i - blk->x;
                    int localC = j - blk->y;
                    if (blk->cellActive(localR, localC)) {
                        c = blk->color;
                        break;
                    }
                }
                std::cout << c;
            } else if (cell.isGate()) {
                std::cout << (char)gates[cell.refIndex].getColorAt(currentStep);
            } else if (cell.isExit()) {
                std::cout << exits[cell.refIndex].color;
            } else {
                std::cout << cell.toChar();
            }
        }
        std::cout << "\n";
    }
}