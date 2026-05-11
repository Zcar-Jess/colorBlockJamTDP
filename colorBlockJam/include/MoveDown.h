#ifndef MOVEDOWN_H
#define MOVEDOWN_H

#include "Operation.h"

class MoveDown : public Operation {
public:
    MoveDown(int blockId, int steps);

    bool   isAppl(Board* b, int currentStep) const override;
    Board* apply (Board* b, int currentStep) const override;
    void   print ()                          const override;
};

#endif