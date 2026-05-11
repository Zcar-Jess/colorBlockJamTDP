#ifndef MOVERIGHT_H
#define MOVERIGHT_H

#include "Operation.h"

class MoveRight : public Operation {
public:
    MoveRight(int blockId, int steps);

    bool   isAppl(Board* b, int currentStep) const override;
    Board* apply (Board* b, int currentStep) const override;
    void   print ()                          const override;
};

#endif