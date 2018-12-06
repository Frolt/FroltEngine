#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

// Forward declarations
class Viewport;
class Engine;
class QExposeEvent;

namespace Ui {
class MainWindow;
}


/**
   @brief The MainWindow class is at the top of the hierarchy in the engine.
    It is the owner of the viewport and engine class
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void init();
    void connectSignalsSlots();

private slots:
    void viewportReady();
    void showFPS();

    void on_Exit_triggered();

public:
    // All QObjects clean up after themself
    Ui::MainWindow *ui{nullptr};
    QWidget *mViewportWidget{nullptr};
    Viewport *mViewport{nullptr};
    Engine *mEngine{nullptr};
};

#endif // MAINWINDOW_H
