
#include "Menu.h"

Menu::Menu(QWidget* parent)
    : QFrame(parent)
{
    moves_num = 0;
    moves_counter = new QLabel(this);
    moves_counter->setText("Moves: " + QString::number(moves_num));
    moves_counter->setAlignment(Qt::AlignCenter);
    moves_counter->setStyleSheet("font-size: 15px; font-weight: bold; color: black; background-color: rgba(0,0,0,0)");
}

void Menu::updateMoves_counter()
{
    moves_counter->setText("Moves: " + QString::number(moves_num));
    moves_counter->update();
}

Menu::~Menu()
{
    
}