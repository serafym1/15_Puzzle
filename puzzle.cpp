
#include "puzzle.h"
#include "qmessagebox.h"
#include "qpropertyanimation.h"

Puzzle::Puzzle(QWidget* parentWidget)
    : QMainWindow(parentWidget)
{
    ui.setupUi(this);

    this->setWindowTitle("15 puzzle");
    this->setWindowIcon(QIcon(":/icon.png"));
    
    movesCounter = new MovesCounter(this);
    movesCounter->setGeometry(GAP_PX, GAP_PX, (TILE_PX_SIZE + GAP_PX) * 2 , 50);
    movesCounter->setStyleSheet("background-color: rgba(255, 0, 255, 150); border-radius: 15px;");
    movesCounter->counterLabel->resize(movesCounter->size());

    automaticSolve = nullptr;
    automaticSolveBtn = new QPushButton(this);
    automaticSolveBtn->setGeometry(movesCounter->x()+ movesCounter->width()+GAP_PX, GAP_PX, movesCounter->width(), 50);
    automaticSolveBtn->setStyleSheet("background-color: rgba(255, 0, 255, 150); border-radius: 15px; font-size: 15px;  font-weight: bold;");
    automaticSolveBtn->setText("Automatic\nsolve");
    automaticSolveBtn->setDisabled(true);

    startAfterManualSortBtn = new QPushButton(this);
    startAfterManualSortBtn->setText("Start");
    startAfterManualSortBtn->setStyleSheet("background-color: rgba(255, 0, 255, 150); border-radius: 15px; font-size: 15px;  font-weight: bold;");
    startAfterManualSortBtn->setGeometry(GAP_PX, GAP_PX, (GAP_PX + TILE_PX_SIZE) * 4 + GAP_PX, 50);
    startAfterManualSortBtn->hide();

    field = new Field(this, this);
    field->setGeometry(GAP_PX, 2 * GAP_PX + 50, (TILE_PX_SIZE + GAP_PX) * FIELD_SIZE + GAP_PX, (TILE_PX_SIZE + GAP_PX) * FIELD_SIZE + GAP_PX);
    field->setStyleSheet("background-color: rgba(255, 0, 255, 150); border-radius: 15px;");
    field->autoShuffleBtn->setGeometry(GAP_PX, GAP_PX, field->width() - 2 * GAP_PX, 2 * TILE_PX_SIZE + GAP_PX);
    field->manualShuffleBtn->setGeometry(GAP_PX, 2 * TILE_PX_SIZE + 3 * GAP_PX, field->width() - 2 * GAP_PX, 2 * TILE_PX_SIZE + GAP_PX);
    connect(automaticSolveBtn, &QPushButton::clicked, this, [=]() {
        automaticSolveBtn->setDisabled(true);
        automaticSolve = new AutomaticSolve(this, field->tilesArray);
        });
    connect(startAfterManualSortBtn, &QPushButton::clicked, this, [=]() {
        automaticSolveBtn->setEnabled(true);
        movesCounter->moves_num = 0;
        movesCounter->updateMovesCounter("Moves: " + QString::number(movesCounter->moves_num));
        movesCounter->show();
        automaticSolveBtn->show();
        startAfterManualSortBtn->hide();
        });

    QSize window_size;
    window_size.setWidth(field->width()+2*GAP_PX);
    window_size.setHeight(field->height() + movesCounter->height() + 3 * GAP_PX);
    this->setFixedSize(window_size);
}

void Puzzle::showResult(QString title, QString message)
{
    qDebug("Is sorted");
    QMessageBox sorted_congratulation(this);
    sorted_congratulation.setWindowTitle(title);
    sorted_congratulation.setText(message);
    sorted_congratulation.setIcon(QMessageBox::Information);
    sorted_congratulation.setStandardButtons(QMessageBox::Retry | QMessageBox::Close);
    int choice = sorted_congratulation.exec();
    switch (choice) {
    case QMessageBox::Retry:
        movesCounter->moves_num = 0;
        movesCounter->updateMovesCounter("Moves: " + QString::number(movesCounter->moves_num));
        automaticSolveBtn->setDisabled(true);
        field->autoShuffleBtn->show();
        field->manualShuffleBtn->show();
        for (int i = 0; i < FIELD_SIZE * FIELD_SIZE; i++) {
            field->tilesArray[i]->setEnabled(true);
        }
        break;
    case QMessageBox::Close:
        QApplication::quit();
        break;
    default:
        qDebug("Error in MessageBox (sorted_congratulation)");
        break;
    }
}

Puzzle::~Puzzle()
{
    delete movesCounter;
    delete field;
    if (automaticSolve) {
        delete automaticSolve;
    }
}
