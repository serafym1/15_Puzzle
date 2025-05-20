#pragma once

#include "qframe.h"
#include "qlabel.h"

class MovesCounter : public QFrame
{
public:
    MovesCounter(QWidget* parent);
    ~MovesCounter();

    int moves_num;
    QLabel* counterLabel;

    void updateMovesCounter(QString counter_text);
};