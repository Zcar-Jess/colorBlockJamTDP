#include "Operation.h"
#include <iostream>

Operation::Operation()
    : name(""), blockId(-1), steps(0)
{}

Operation::Operation(const std::string& n, int id, int s)
    : name(n), blockId(id), steps(s)
{}

Operation::~Operation() {}

// Implementaciones base: la subclase siempre las sobreescribe
bool Operation::isAppl(Board*, int) const {
    return false;
}

Board* Operation::apply(Board*, int) const {
    return nullptr;
}

void Operation::print() const {
    std::cout << "Operation: " << name << "\n";
}