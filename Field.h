#pragma once

#include "header.h"
#include "qframe.h"
#include "Tile.h"
#include "puzzle.h"

class Puzzle;

class Field : public QFrame
{
public:
    Field(QWidget* parentWidget, Puzzle* parent);
    ~Field();
    
    Puzzle* puzzle;
    Tile* tilesArray[FIELD_SIZE * FIELD_SIZE];
    Tile* tile0;
    QPushButton* autoShuffleBtn;
    QPushButton* manualShuffleBtn;

    bool isNear(Tile* tile1, Tile* tile2);
    void moveTile(Tile* tile);
    bool isSorted();
    void automaticShuffle();
    void manualShuffle();
};