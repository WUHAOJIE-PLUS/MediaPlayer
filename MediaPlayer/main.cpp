#include "cmainwindow.h"
#include <QApplication>
#include "ccombinationplay.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CMainWindow w;
    // CcombinationPlay w;

    w.show();
    return a.exec();
}
