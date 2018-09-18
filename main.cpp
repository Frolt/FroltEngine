#include "mainwindow.h"
#include <QApplication>
#include <QDebug>
#include <iostream>
#include "engine.h"

int main(int argc, char *argv[])
{
    // TODO Move to viewport's constructor
    QCoreApplication::setAttribute(Qt::AA_UseDesktopOpenGL);
    QApplication app(argc, argv);
    MainWindow window;
    window.show();

    return app.exec();
}
