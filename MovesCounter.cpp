
#include "MovesCounter.h"

MovesCounter::MovesCounter(QWidget* parent)
    : QFrame(parent)
{
    moves_num = 0;
    counterLabel = new QLabel(this);
    updateMovesCounter("Moves: " + QString::number(moves_num));
    counterLabel->setAlignment(Qt::AlignCenter);
    counterLabel->setStyleSheet("font-size: 15px; font-weight: bold; color: black; background-color: rgba(0,0,0,0)");
}

void MovesCounter::updateMovesCounter(QString counter_text)
{
    counterLabel->setText(counter_text);
    counterLabel->update();
    counterLabel->repaint();
}

MovesCounter::~MovesCounter()
{
    
}