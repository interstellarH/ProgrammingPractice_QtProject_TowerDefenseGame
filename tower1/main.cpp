#include "mainwindow.h"
#include "start.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    start w;
    w.paintEvent(NULL);
    w.show();
    return a.exec();
}
