
#include "puzzle.h"
#include "qpropertyanimation.h"
#include "qmessagebox.h"

puzzle::puzzle(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    this->setWindowTitle("15 puzzle");
    this->setWindowIcon(QIcon(":/icon.png"));
    
    menu = new Menu(this);
    menu->setGeometry(PX_GAP, PX_GAP, (TILE_PX_SIZE + PX_GAP) * 2 , 50);
    menu->setStyleSheet("background-color: rgba(255, 0, 255, 150); border-radius: 15px;");
    menu->moves_counter->resize(menu->size());

    automatic_solve_btn = new QPushButton(this);
    automatic_solve_btn->setGeometry(menu->x()+ menu->width()+PX_GAP, PX_GAP, menu->width(), 50);
    automatic_solve_btn->setStyleSheet("background-color: rgba(255, 0, 255, 150); border-radius: 15px; font-size: 15px;  font-weight: bold;");
    automatic_solve_btn->setText("Automatic\nsolve");
    automatic_solve_btn->setDisabled(true);
    
    //puzzle* parentW = qobject_cast<puzzle*>(this->parentWidget());
    field = new Field(this);
    field->setGeometry(PX_GAP, 2 * PX_GAP + 50, (TILE_PX_SIZE + PX_GAP) * FIELD_SIZE + PX_GAP, (TILE_PX_SIZE + PX_GAP) * FIELD_SIZE + PX_GAP);
    field->setStyleSheet("background-color: rgba(255, 0, 255, 150); border-radius: 15px;");
    for (int i = 0; i < FIELD_SIZE*FIELD_SIZE-1; i++) {
        connect(field->tilesArray[i], &QPushButton::clicked, this, [=]() {
            Tile* clickedTile = field->tilesArray[i];
            if (field->isNear(clickedTile, field->tile0)) {
                QPropertyAnimation* anim = new QPropertyAnimation(clickedTile, "pos", this);
                anim->setDuration(200);
                anim->setStartValue(clickedTile->pos());
                anim->setEndValue(field->tile0->pos());
                anim->setEasingCurve(QEasingCurve::InOutCubic);
                field->tile0->move(clickedTile->pos());
                anim->start();
                std::swap(field->tile0->index, clickedTile->index);
                
                menu->moves_num++;
                menu->updateMoves_counter();
                if (field->isSorted()) {
                    showResult();
                }
            }
            });
    }
    field->startButton->resize(field->size());
    connect(field->startButton, &QPushButton::clicked, this, [=]() {
        field->shuffle();
        field->startButton->hide();
        automatic_solve_btn->setEnabled(true);
        });
    connect(automatic_solve_btn, &QPushButton::clicked, this, [=]() {
        automatic_solve_btn->setDisabled(true);
        automaticSolve = new AutomaticSolve(this, field->tilesArray);
        
        });

    QSize window_size;
    window_size.setWidth(field->width()+2*PX_GAP);
    window_size.setHeight(field->height() + menu->height() + 3 * PX_GAP);
    this->setFixedSize(window_size);
}

void puzzle::showResult()
{
    qDebug("Is sorted");
    QMessageBox sorted_congratulation(this);
    sorted_congratulation.setWindowTitle("Congratulations!!!");
    sorted_congratulation.setText("You solved puzzle!\nNumber of moves:  " + QString::number(menu->moves_num));
    sorted_congratulation.setIcon(QMessageBox::Information);
    sorted_congratulation.setStandardButtons(QMessageBox::Retry | QMessageBox::Close);
    int choice = sorted_congratulation.exec();
    switch (choice) {
    case QMessageBox::Retry:
        menu->moves_num = 0;
        menu->updateMoves_counter();
        automatic_solve_btn->setDisabled(true);
        field->startButton->show();
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

puzzle::~puzzle()
{
    delete menu;
    delete field;
    if (automaticSolve) {
        delete automaticSolve;
    }
}
