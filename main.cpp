#include "mainwindow.h"
#include <QApplication>
#include <QDebug>
#include <QSplashScreen>
#include <QTimer>
#include <iostream>
#include "engine.h"
#include "path.h"

/** @mainpage Frolt Engine
@section intro_sec Introduction
    "Frolt %Engine%" is a game engine made with OpenGL and QT Creator.  \n
    It uses a right hand coordinate system with -z pointing forward, x pointing right, and y pointing upwards  \n
    The game engine uses ECS (Entity–component–system)  \n
    Entities works as a simple unsigned int tag to bind components to an entity. \n
    Components simply used as data for the systems to work on. \n
    Systems are responsible for logic, they are initialized with a bit mask \n
    that specifies which entities that particular system should pay attention to.
@section install_sec Installation
@subsection step1 Step 1: Changing build directory
    Need to build the project in the root directory.  \n
    In the QT-editor, go to the projects tab(left side of screen).  \n
    Change debug and release build directory to inside the project directory. Mine is for example  \n
    C:\\......\\FroltEngine\\build-FroltEngine-MSVC2017_64bit-Debug  \n
@section deploy_sec Deploy project for windows:
    1. controlpanel -> system -> advanced system settings -> enviroment variables  \n
    2. add "<qt-dir>/<qt-version>/bin" folder to the path. Mine is for example  \n
    C:\Qt\5.10.1\msvc2017_64\bin  \n
    3. open CMD and run "windeployqt.exe <path-to-exe-file-in-build-directory>" from the bin folder \n
    4. copy the files from "FroltEngine\Libraries\libs" .exe file build directory \n
@section lib_sec External libraries used
    ASSIMP (Asset importer) for loading 3D meshes \n
    http://www.assimp.org/ \n
    GLM (OpenGL Mathematics) for math related functions \n
    glm is installed but not used in the engine \n
    https://glm.g-truc.net/0.9.9/index.html
 */

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Splash screen
    QPixmap pixmap ("../Assets/logo2.jpg");
    QSplashScreen splash(pixmap);
    QFont font("FreeSans", 48, QFont::Bold);
    splash.setFont(font);
    splash.show();
    splash.showMessage(QObject::tr("Loading..."), Qt::AlignBottom | Qt::AlignHCenter);

    MainWindow window;
    window.show();
    splash.close();

    return app.exec();
}
