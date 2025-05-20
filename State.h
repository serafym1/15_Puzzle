#pragma once

#include <vector>
#include "Tile.h"
#include "priority_queue.h"

enum ZeroMovesDir
{
    UP, DOWN, LEFT, RIGHT
};

struct POS {
    POS() = default;
    POS(int x, int y) {
        this->x = x;
        this->y = y;
    }

    int x;
    int y;
};

struct CompareState;

class State
{
public:
    State(Tile** sourceArray, POS* corectPos);
    State(State* parent, POS* corectPos, ZeroMovesDir zero_move_dir);
    ~State();

    

    POS* correctPos;
    POS zero_pos;
    int current_moves;
    int heuristic;
    int tilesMatrix[FIELD_SIZE][FIELD_SIZE];

    State* parent_state;

    void calculateHeuristic();
    bool isSame(const State* other);
    bool canMove(ZeroMovesDir zero_moves);
};

struct CompareState {
    bool operator()(State* a, State* b) const {
        int f_a = 2*a->current_moves + 3*a->heuristic;
        int f_b = 2*b->current_moves + 3*b->heuristic;

        if (f_a != f_b) {
            return f_a > f_b;
        }
        return a->heuristic > b->heuristic;
    }
};