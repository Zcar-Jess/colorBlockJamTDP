// src/ClosedSet.cpp
#include "ClosedSet.h"

ClosedSet::ClosedSet(int nb) : numBuckets(nb), size(0) {
    buckets = new HashNode*[numBuckets];
    for (int i = 0; i < numBuckets; i++) {
        buckets[i] = nullptr;
    }
}

ClosedSet::~ClosedSet() {
    for (int i = 0; i < numBuckets; i++) {
        HashNode* node = buckets[i];
        while (node) {
            HashNode* next = node->next;
            delete node;  // NO libera el GameState, lo hace el Solver
            node = next;
        }
    }
    delete[] buckets;
}

// Hash basado en posiciones de bloques + paso actual.
// Usa numeros primos para distribuir bien los valores.
int ClosedSet::computeHash(GameState* s) const {
    unsigned int h = (unsigned int)s->currentStep * 983;

    Board* b = s->board;
    for (int i = 0; i < b->numBlocks; i++) {
        Block* blk = b->blocks[i];
        h = h * 31 + (unsigned int)(blk->id  * 1000003);
        h = h * 31 + (unsigned int)(blk->x   * 997);
        h = h * 31 + (unsigned int)(blk->y   * 991);
    }

    return (int)(h % (unsigned int)numBuckets);
}

void ClosedSet::add(GameState* s) {
    int idx = computeHash(s);

    // Insertar al inicio del bucket (chaining)
    HashNode* node = new HashNode(s);
    node->next     = buckets[idx];
    buckets[idx]   = node;
    size++;
}

bool ClosedSet::contains(GameState* s) const {
    int idx = computeHash(s);

    HashNode* node = buckets[idx];
    while (node) {
        if (node->state->equals(s)) return true;
        node = node->next;
    }
    return false;
}