#pragma once

#include "puzzle.h"
#include "Tile.h"
#include "State.h"
#include "queue"
#include "stack"
#include "existing_states_tree.h"

class puzzle;

class AutomaticSolve {
public:
    AutomaticSolve(puzzle* parent, Tile** sourceArray);
    ~AutomaticSolve();

    POS correctPos[field_size * field_size];

    puzzle* parentW;

    std::priority_queue<State*, std::vector<State*>, CompareState> states_queue;
    ExistingStatesTree existing_states;
    std::stack<int> swapOrder;

    //bool check_unique_and_add(State* currentState);
    void automatic_solve();
};