#include "tsm_mw.h"
#include <QApplication>
#include <QTranslator>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTranslator qtTranslator;
    qtTranslator.load(a.applicationDirPath() + "/tsm_" + QLocale::system().name() + ".qm");
    a.installTranslator(&qtTranslator);
    tsm_mw w;
    w.showMaximized();
    return a.exec();
}
