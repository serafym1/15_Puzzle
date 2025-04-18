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
    int prognised_heuristic;
    int tilesMatrix[4][4];

    State* parent_state;

    void calculate_heuristic();
    bool check_unique_and_add(std::vector<State*>& existing_states, priority_queue<State*, CompareState>& states_queue);
    bool is_same(const State* other);
    bool can_move(ZeroMovesDir zero_moves);
};

struct CompareState {
    bool operator()(State* a, State* b) const {
        int f_a = 2*a->current_moves + 3*a->prognised_heuristic;
        int f_b = 2*b->current_moves + 3*b->prognised_heuristic;

        if (f_a != f_b) {
            return f_a < f_b;
        }
        return a->prognised_heuristic < b->prognised_heuristic;
    }
};