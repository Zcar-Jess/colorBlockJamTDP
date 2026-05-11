#ifndef MOVEUP_H
#define MOVEUP_H

#include "Operation.h"

// Mueve un bloque hacia arriba N celdas.
class MoveUp : public Operation {
public:
    // blockId: ID del bloque a mover
    // steps: cantidad de celdas hacia arriba
    MoveUp(int blockId, int steps);

    bool   isAppl(Board* b, int currentStep) const override;
    Board* apply (Board* b, int currentStep) const override;
    void   print ()                          const override;
};

#endif