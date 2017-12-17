#include "tsm_mw.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    tsm_mw w;
    w.showMaximized();
    return a.exec();
}
