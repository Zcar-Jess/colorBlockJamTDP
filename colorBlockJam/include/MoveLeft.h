#ifndef MOVELEFT_H
#define MOVELEFT_H

#include "Operation.h"

class MoveLeft : public Operation {
public:
    MoveLeft(int blockId, int steps);

    bool   isAppl(Board* b, int currentStep) const override;
    Board* apply (Board* b, int currentStep) const override;
    void   print ()                          const override;
};

#endif