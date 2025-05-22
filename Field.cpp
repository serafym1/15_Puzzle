
#include "Field.h"
#include "qpropertyanimation.h"

//class Puzzle;

Field::Field(QWidget* parentWidget, Puzzle* parent)
    : QFrame(parentWidget), puzzle(parent)
{
    int index = 0;
    for (int i = 0; i < FIELD_SIZE; i++) {
        for (int j = 0; j < FIELD_SIZE; j++) {
            tilesArray[index] = new Tile(j, i, index, this);
            index++;
        }
    }
    tile0 = tilesArray[FIELD_SIZE * FIELD_SIZE - 1];

    autoShuffleBtn = new QPushButton("Automatic shuffle", this);
    autoShuffleBtn->setStyleSheet("background-color: rgba(255, 150, 255, 255); border-radius: 10px;");
    manualShuffleBtn = new QPushButton("Manual shuffle", this);
    manualShuffleBtn->setStyleSheet("background-color: rgba(255, 150, 255, 255); border-radius: 10px;");

    for (int i = 0; i < FIELD_SIZE * FIELD_SIZE - 1; i++) {
        connect(tilesArray[i], &QPushButton::clicked, this, [=]() {
            moveTile(tilesArray[i]);
            });
    }
    connect(autoShuffleBtn, &QPushButton::clicked, this, [=]() {
        automaticShuffle();
        });
    connect(manualShuffleBtn, &QPushButton::clicked, this, [=]() {
        manualShuffle();
        });
}

bool Field::isNear(Tile* tile1, Tile* tile2)
{
    return (abs(tile1->x() - tile2->x()) + abs(tile1->y() - tile2->y()) == (GAP_PX + TILE_PX_SIZE));
}

void Field::automaticShuffle()
{
    int last_moved = 0;
    int i = 0;
    while (i < 1000) {                  // It is prowed that it wouldn`t be more complicated with more than about 80 moves to automaticShuffle
        int rand_index = rand() % 15;   // just swapping isn't hard and to lower possibility of cycles I made 1000
        if (isNear(tile0, tilesArray[rand_index]) && rand_index != last_moved) {
            QPoint temp = tile0->pos();
            tile0->move(tilesArray[rand_index]->pos());
            tilesArray[rand_index]->move(temp);
            std::swap(tile0->index, tilesArray[rand_index]->index);
            i++;
            last_moved = rand_index;
        }
    }
    manualShuffleBtn->hide();
    autoShuffleBtn->hide();
    puzzle->automaticSolveBtn->setEnabled(true);
}

bool Field::isSorted()
{
    if (puzzle->startAfterManualSortBtn->isVisible()) {
        return false;
    }
    for (int i = 0; i < FIELD_SIZE * FIELD_SIZE - 1; i++) {
        if (tilesArray[i]->index != i) {
            return false;
        }
    }
    return true;
}

void Field::moveTile(Tile* tile)
{
    if (!isNear(tile, tile0)) {
        return;
    }
    QPropertyAnimation* anim = new QPropertyAnimation(tile, "pos", this);
    connect(anim, &QPropertyAnimation::finished, anim, &QObject::deleteLater);
    anim->setDuration(200);
    anim->setStartValue(tile->pos());
    anim->setEndValue(tile0->pos());
    anim->setEasingCurve(QEasingCurve::InOutCubic);
    tile0->move(tile->pos());
    anim->start();
    std::swap(tile0->index, tile->index);

    puzzle->movesCounter->moves_num++;
    puzzle->movesCounter->updateMovesCounter("Moves: " + QString::number(puzzle->movesCounter->moves_num));
    if (isSorted()) {
        puzzle->showResult("Congratulations!!!", "You solved puzzle!\nNumber of moves:  " + QString::number(puzzle->movesCounter->moves_num));
    }
}

void Field::manualShuffle() {
    manualShuffleBtn->hide();
    autoShuffleBtn->hide();
    puzzle->movesCounter->hide();
    puzzle->automaticSolveBtn->hide();
    puzzle->startAfterManualSortBtn->show();
    puzzle->automaticSolveBtn->setEnabled(true);
}

Field::~Field()
{
    for (int i = 0; i < FIELD_SIZE * FIELD_SIZE; ++i) {
        delete tilesArray[i];
    }
    delete autoShuffleBtn;
}
