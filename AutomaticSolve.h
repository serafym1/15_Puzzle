#pragma once

#include "puzzle.h"
#include "Tile.h"
#include "State.h"
#include "queue"
#include "stack"
#include "ExistingStatesTree.h"

class Puzzle;

class AutomaticSolve {
public:
    AutomaticSolve(Puzzle* parent, Tile** sourceArray);
    ~AutomaticSolve();

    POS correctPos[FIELD_SIZE * FIELD_SIZE];

    Puzzle* puzzle;

    std::priority_queue<State*, std::vector<State*>, CompareState> statesQueue;
    ExistingStatesTree existingStates;
    std::stack<int> swapOrder;

    void automaticSolve();
};