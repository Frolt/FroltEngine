#include "mainwindow.h"
#include <QApplication>
#include <QDebug>
#include <iostream>
#include "engine.h"

int main(int argc, char *argv[])
{
    // TODO snakk med Ole
//    QCoreApplication::setAttribute(Qt::AA_UseDesktopOpenGL);
    QApplication app(argc, argv);
    MainWindow window;
    window.show();

    return app.exec();
}
