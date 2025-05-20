#pragma once

#include "header.h"
#include <QtWidgets/QMainWindow>
#include "AutomaticSolve.h"
#include "MovesCounter.h"
#include "Field.h"
#include "ui_puzzle.h"
#include <QtWidgets/QApplication>

class AutomaticSolve;
class Field;

class Puzzle : public QMainWindow
{
    Q_OBJECT

public:
    Puzzle(QWidget* parent = nullptr);
    ~Puzzle();

    MovesCounter* movesCounter;
    Field* field;
    AutomaticSolve* automaticSolve;
    QPushButton* automaticSolveBtn;
    QPushButton* startAfterManualSortBtn;

    void showResult(QString title, QString message);

private:
    Ui::puzzleClass ui;
};
