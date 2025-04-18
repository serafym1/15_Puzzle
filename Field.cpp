
#include "Field.h"

Field::Field(QWidget* parent)
    : QFrame(parent)
{
    int index = 0;
    for (int i = 0; i < field_size; i++) {
        for (int j = 0; j < field_size; j++) {
            tilesArray[index] = new Tile(j, i, index, this);
            index++;
        }
    }
    tile0 = tilesArray[field_size * field_size - 1];

    startButton = new QPushButton("Start", this);

    startButton->setStyleSheet("background-color: rgba(255, 150, 255, 255); border-radius: 15px;");

}

bool Field::isNear(Tile* tile1, Tile* tile2)
{
    return (abs(tile1->x() - tile2->x()) + abs(tile1->y() - tile2->y()) == (gap + tile_size));
}

void Field::shuffle()
{
    int last_moved = 0;
    int i = 0;
    while (i < 50) { // It is prowed that it wouldn`t be more complicated with more than about 100 moves to shuffle
        int rand_index = rand() % 15;
        if (isNear(tile0, tilesArray[rand_index]) && rand_index != last_moved) {
            QPoint temp = tile0->pos();
            tile0->move(tilesArray[rand_index]->pos());
            tilesArray[rand_index]->move(temp);
            std::swap(tile0->index, tilesArray[rand_index]->index);
            i++;
            last_moved = rand_index;
        }
    }
}

bool Field::isSorted()
{
    for (int i = 0; i < field_size * field_size - 1; i++) {
        if (tilesArray[i]->index != i) {
            return false;
        }
    }
    return true;
}

Field::~Field()
{
    for (int i = 0; i < field_size * field_size; ++i) {
        delete tilesArray[i];
    }
    delete startButton;
}
