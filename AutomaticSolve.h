#pragma once

#include "puzzle.h"
#include "Tile.h"
#include "State.h"
#include "queue"
#include "stack"
#include "ExistingStatesTree.h"

class puzzle;

class AutomaticSolve {
public:
    AutomaticSolve(puzzle* parent, Tile** sourceArray);
    ~AutomaticSolve();

    POS correctPos[FIELD_SIZE * FIELD_SIZE];

    puzzle* parentW;

    std::priority_queue<State*, std::vector<State*>, CompareState> states_queue;
    ExistingStatesTree existing_states;
    std::stack<int> swap_order;

    void automatic_solve();
};