#pragma once

#include "qframe.h"
#include "qlabel.h"

class Menu : public QFrame
{
public:
    Menu(QWidget* parent);
    ~Menu();

    int moves_num;
    QLabel* moves_counter;

    void updateMoves_counter();
};