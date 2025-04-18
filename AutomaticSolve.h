#pragma once

#include "puzzle.h"
#include "Tile.h"
#include "State.h"
#include <stack>

class puzzle;

class AutomaticSolve {
public:
    AutomaticSolve(puzzle* parent, Tile** sourceArray);
    ~AutomaticSolve();

    POS correctPos[field_size * field_size];

    puzzle* parentW;

    priority_queue<State*, CompareState> states_queue;
    std::vector<State*> existing_states;
    std::stack<int> swapOrder;

    void automatic_solve();
};