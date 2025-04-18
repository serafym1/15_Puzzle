#pragma once

#include "header.h"
#include "qframe.h"
#include "Tile.h"

class Field : public QFrame
{
public:
    Field(QWidget* parent);
    ~Field();

    Tile* tilesArray[field_size * field_size];
    Tile* tile0;
    QPushButton* startButton;

    bool isNear(Tile* tile1, Tile* tile2);
    void shuffle();
    bool isSorted();
};