#include "ClosedSet.h"

ClosedSet::ClosedSet(int cap)
    : size(0), capacity(cap)
{
    states = new GameState*[capacity];
}

ClosedSet::~ClosedSet() {
    delete[] states;
}

void ClosedSet::add(GameState* s) {
    if (size >= capacity) {
        capacity *= 2;

        GameState** newArr = new GameState*[capacity];

        for (int i = 0; i < size; i++) {
            newArr[i] = states[i];
        }

        delete[] states;
        states = newArr;
    }

    states[size++] = s;
}

bool ClosedSet::contains(GameState* s) const {
    for (int i = 0; i < size; i++) {
        if (states[i]->equals(s)) {
            return true;
        }
    }

    return false;
}