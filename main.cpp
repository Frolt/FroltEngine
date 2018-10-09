#include "mainwindow.h"
#include <QApplication>
#include <QDebug>
#include <iostream>
#include "engine.h"

#include <optional>
#include <cstddef>

int main(int argc, char *argv[])
{
    std::byte byte; // c++17
    // TODO snakk med Ole
//    QCoreApplication::setAttribute(Qt::AA_UseDesktopOpenGL);
    QApplication app(argc, argv);
    MainWindow window;
    window.show();

    return app.exec();
}
