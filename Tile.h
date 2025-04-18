#pragma once

#include "qpushbutton.h"

class Tile : public QPushButton
{
public:
    Tile(int pos_x, int pos_y, int num, QWidget* parent);
    ~Tile();

    int index;
};
