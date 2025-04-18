#pragma once

#include "header.h"
#include <QtWidgets/QMainWindow>
#include "AutomaticSolve.h"
#include "Menu.h"
#include "Field.h"
#include "ui_puzzle.h"
#include <QtWidgets/QApplication>

class AutomaticSolve;

class puzzle : public QMainWindow
{
    Q_OBJECT

public:
    puzzle(QWidget* parent = nullptr);
    ~puzzle();

    Menu* menu;
    Field* field;
    AutomaticSolve* automaticSolve;
    QPushButton* automatic_solve_btn;

    void showResult();

private:
    Ui::puzzleClass ui;
};
