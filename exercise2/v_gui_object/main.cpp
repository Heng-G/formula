#include "mainwindow.h"

#include <QApplication>
#include <e.h>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    e e;

    e.setWindowTitle(QStringLiteral("name"));
    e.show();
    e.exec();

    w.setWindowTitle("Control Bar");
    w.show();
    return a.exec();
}
