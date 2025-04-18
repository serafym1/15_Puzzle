
#include "header.h"
#include "State.h"

State::State(Tile** sourceArray, POS* correctPos) {
    parent_state = nullptr;
    current_moves = 0;
    this->correctPos = correctPos;
    prognised_heuristic = 0;
    for (int i = 0; i < field_size; i++) {
        for (int j = 0; j < field_size; j++) {
            int index = i * field_size + j;
            int m = sourceArray[index]->index / 4;
            int n = sourceArray[index]->index % 4;
            tilesMatrix[m][n] = sourceArray[index]->text().toInt();
            if (tilesMatrix[m][n] == 0) {
                zero_pos = POS(n, m);
            }
        }
    }
    calculate_heuristic();
}

State::State(State* parent, POS* correctPos, ZeroMovesDir zero_move_dir) {
    parent_state = parent;

    current_moves = 0;
    State* copy = this;
    do {
        current_moves++;
        copy = copy->parent_state;
    } while (copy->parent_state != nullptr);

    this->correctPos = correctPos;
    prognised_heuristic = 0;
    zero_pos = parent->zero_pos;
    //tilesMatrix = new std::vector<std::vector<int>>(4, std::vector<int>(4));
    for (int i = 0; i < field_size; i++) {
        for (int j = 0; j < field_size; j++) {
            int index = i * field_size + j;
            tilesMatrix[i][j] = parent_state->tilesMatrix[i][j];
        }
    }
    switch (zero_move_dir) {
    case UP:
        std::swap(tilesMatrix[zero_pos.y][zero_pos.x], tilesMatrix[zero_pos.y - 1][zero_pos.x]);
        zero_pos.y--;
        break;
    case DOWN:
        std::swap(tilesMatrix[zero_pos.y][zero_pos.x], tilesMatrix[zero_pos.y + 1][zero_pos.x]);
        zero_pos.y++;
        break;
    case LEFT:
        std::swap(tilesMatrix[zero_pos.y][zero_pos.x], tilesMatrix[zero_pos.y][zero_pos.x - 1]);
        zero_pos.x--;
        break;
    case RIGHT:
        std::swap(tilesMatrix[zero_pos.y][zero_pos.x], tilesMatrix[zero_pos.y][zero_pos.x + 1]);
        zero_pos.x++;
        break;
    }
    calculate_heuristic();
}

void State::calculate_heuristic()
{
    int misplased = 0;
    for (int i = 0; i < field_size; i++) {
        for (int j = 0; j < field_size; j++) {
            if (tilesMatrix[i][j] != 0) {
                int tile = tilesMatrix[i][j];
                prognised_heuristic += abs(i - correctPos[tile].y) + abs(j - correctPos[tile].x);
            }
        }
    }
    
}

bool State::is_same(const State* other) {
    bool are_same = true;
    if (this->prognised_heuristic != other->prognised_heuristic) {
        are_same = false;
    }
    else {
        for (int i = 0; i < field_size; ++i) {
            for (int j = 0; j < field_size; ++j) {
                if (this->tilesMatrix[i][j] != other->tilesMatrix[i][j]) {
                    are_same = false;
                    break;
                }
            }
            if (!are_same) {
                break;
            }
        }
    }
    return are_same;
}

bool State::check_unique_and_add(std::vector<State*>& existing_states, priority_queue<State*, CompareState>& states_queue)
{
    for (State* existing : existing_states) {
        if (this->is_same(existing)) {
            if (this->current_moves < existing->current_moves) {
                *existing = *this;
                states_queue.push(this);
                return true;
            }
            return false; 
        }
        
    }
    existing_states.push_back(this);
    states_queue.push(this);

    return true;
}

bool State::can_move(ZeroMovesDir zero_move)
{
    switch (zero_move) {
    case UP:
        if (zero_pos.y != 0) {
            return true;
        }
        return false;
    case DOWN:
        if (zero_pos.y != 3) {
            return true;
        }
        return false;
    case LEFT:
        if (zero_pos.x != 0) {
            return true;
        }
        return false;
    case RIGHT:
        if (zero_pos.x != 3) {
            return true;
        }
        return false;
    default:
        qDebug("Error in switch (function canMoveAndDontReturn)");
        return false;
        break;
    }
    return false;
}

State::~State() {
    
}