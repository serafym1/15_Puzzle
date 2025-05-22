
#include "puzzle.h"
#include <iostream>
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
int main(int argc, char *argv[])
{
    srand(time(NULL));
    QApplication a(argc, argv);
    Puzzle w;
    w.show();
    return a.exec();
}
