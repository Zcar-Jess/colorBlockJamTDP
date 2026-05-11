#include "MoveSequence.h"
#include <iostream>

void MoveSequence::apply(
    Board* board,
    const char* seq
) {
    int i = 0;
    int step = 0;

    while (seq[i] != '\0') {

        char dir = seq[i++];

        int id = 0;

        while (seq[i] >= '0' &&
               seq[i] <= '9') {

            id = id * 10 +
                 (seq[i] - '0');

            i++;
        }

        i++; // saltar coma

        int dist = 0;

        while (seq[i] >= '0' &&
               seq[i] <= '9') {

            dist = dist * 10 +
                   (seq[i] - '0');

            i++;
        }

        board->moveBlock(
            id,
            dir,
            dist,
            step
        );

        step++;

        board->display(step);

        std::cout<< "-------------------\n";
    }
}