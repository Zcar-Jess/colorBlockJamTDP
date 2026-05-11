#ifndef BOARDPARSER_H
#define BOARDPARSER_H

#include "Board.h"

class BoardParser {
public:

    static Board* loadFromFile(
        const char* filename
    );
};

#endif