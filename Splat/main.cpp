#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    // Making the output window size fixed.
    w.setFixedSize(w.width(),w.height());

    w.show();

    return a.exec();
}
