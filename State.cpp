
#include "header.h"
#include "State.h"

State::State(Tile** sourceArray, POS* correctPos) {
    parent_state = nullptr;
    current_moves = 0;
    this->correctPos = correctPos;
    heuristic = 0;
    for (int i = 0; i < FIELD_SIZE; i++) {
        for (int j = 0; j < FIELD_SIZE; j++) {
            int index = i * FIELD_SIZE + j;
            int m = sourceArray[index]->index / 4;
            int n = sourceArray[index]->index % 4;
            tilesMatrix[m][n] = sourceArray[index]->text().toInt();
            if (tilesMatrix[m][n] == 0) {
                zero_pos = POS(n, m);
            }
        }
    }
    calculateHeuristic();
}

State::State(State* parent, POS* correctPos, ZeroMovesDir zero_move_dir) {
    parent_state = parent;

    current_moves = this->parent_state->current_moves + 1;

    this->correctPos = correctPos;
    zero_pos = parent->zero_pos;
    for (int i = 0; i < FIELD_SIZE; i++) {
        for (int j = 0; j < FIELD_SIZE; j++) {
            int index = i * FIELD_SIZE + j;
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
    calculateHeuristic();
}

void State::calculateHeuristic()
{
    heuristic = 0;
    int linear_conflicts = 0;

    for (int i = 0; i < FIELD_SIZE; i++) {
        for (int j = 0; j < FIELD_SIZE; j++) {
            int tile = tilesMatrix[i][j];
            if (tile == 0) continue;

            int goal_y = correctPos[tile].y;
            int goal_x = correctPos[tile].x;

            heuristic += abs(i - goal_y) + abs(j - goal_x);
        }
    }

    for (int row = 0; row < FIELD_SIZE; row++) {
        for (int i = 0; i < FIELD_SIZE - 1; i++) {
            int tile1 = tilesMatrix[row][i];
            if (tile1 == 0 || correctPos[tile1].y != row) continue;

            for (int j = i + 1; j < FIELD_SIZE; j++) {
                int tile2 = tilesMatrix[row][j];
                if (tile2 == 0 || correctPos[tile2].y != row) continue;

                if (correctPos[tile1].x > correctPos[tile2].x) {
                    linear_conflicts++;
                }
            }
        }
    }
    for (int col = 0; col < FIELD_SIZE; col++) {
        for (int i = 0; i < FIELD_SIZE - 1; i++) {
            int tile1 = tilesMatrix[i][col];
            if (tile1 == 0 || correctPos[tile1].x != col) continue;

            for (int j = i + 1; j < FIELD_SIZE; j++) {
                int tile2 = tilesMatrix[j][col];
                if (tile2 == 0 || correctPos[tile2].x != col) continue;

                if (correctPos[tile1].y > correctPos[tile2].y) {
                    linear_conflicts++;
                }
            }
        }
    }

    heuristic += 2 * linear_conflicts;
}



bool State::isSame(const State* other) {
    bool are_same = true;
    if (this->heuristic != other->heuristic) {
        are_same = false;
    }
    else {
        for (int i = 0; i < FIELD_SIZE; ++i) {
            for (int j = 0; j < FIELD_SIZE; ++j) {
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

bool State::canMove(ZeroMovesDir zero_move)
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