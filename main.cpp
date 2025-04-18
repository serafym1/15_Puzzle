
#include "puzzle.h"
#include <iostream>
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
int main(int argc, char *argv[])
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    srand(time(NULL));
    QApplication a(argc, argv);
    puzzle w;
    w.show();
    return a.exec();
}
