#include "widget.h"
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QApplication>
#include <QScreen>
#include <QDebug>

#include <QDir>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QDir::setCurrent(QCoreApplication::applicationDirPath());
    Widget w;
    w.show();

    return a.exec();
}
