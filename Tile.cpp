
#include "header.h"
#include "Tile.h"

Tile::Tile(int pos_x, int pos_y, int num, QWidget* parent)
    : QPushButton(parent)
{
    index = num;
    if ((num + 1) != 16) {
        setStyleSheet("QPushButton { border: 0px solid cyan; font-weight: bold; background-color: cyan; border-radius: 10px}");
        setText(QString::number(num + 1));
        show();
    }
    else {
        hide();
        setText(QString::number(0));
    }
    move(pos_x * (gap + tile_size) + gap, pos_y * (gap + tile_size) + gap);
    setFixedSize(tile_size, tile_size);
}

Tile::~Tile()
{

}