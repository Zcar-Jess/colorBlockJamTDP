#ifndef BLOCK_H
#define BLOCK_H

// Representa un bloque movil del tablero Color Block Jam.
// Analogia con el ejemplo de envases: el bloque es como un "envase"
// que tiene estado (posicion, color) y puede cambiar con operaciones.

class Block {
private:
    int id;         // Identificador unico del bloque
    char color;     // Color del bloque (letra minuscula, ej: 'a', 'b')
    int width;      // Ancho del bloque (columnas que ocupa su bounding box)
    int height;     // Alto del bloque  (filas que ocupa su bounding box)
    int x;          // Fila de la esquina (0,0) del bloque en el tablero
    int y;          // Columna de la esquina (0,0) del bloque en el tablero
    int colorLock;  // 0=libre, 1-9=bloqueado hasta que salgan N salidas
    bool* geometry; // Arreglo booleano de width*height (true=celda del bloque)

public:
    // Constructor principal
    Block(int id, char color, int width, int height,
          int x, int y, int colorLock, const bool* geometry);

    // Constructor de copia (necesario para duplicar estados en A*)
    Block(const Block& other);

    // Operador de asignacion
    Block& operator=(const Block& other);

    // Destructor
    ~Block();

    // --- Getters ---
    int   getId()       const;
    char  getColor()    const;
    int   getWidth()    const;
    int   getHeight()   const;
    int   getX()        const;
    int   getY()        const;
    int   getColorLock() const;

    // Retorna true si la celda local (row, col) pertenece al bloque
    bool cellActive(int row, int col) const;

    // --- Setters de posicion (usados al mover el bloque) ---
    void setX(int newX);
    void setY(int newY);

    // Decrementa el bloqueo de color (cuando una salida del mismo color se libera)
    void decrementLock();

    // Compara dos bloques (util para comparar estados en ClosedSet)
    bool equals(const Block& other) const;

    // Muestra el bloque por consola (para debug y tests)
    void print() const;
};

#endif