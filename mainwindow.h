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
    void on_messageButton_clicked();
    void on_Exit_triggered();

private:
    // All QObjects clean up after themself
    Ui::MainWindow *ui{nullptr};
    QWidget *mViewportWidget{nullptr};
    Viewport *mViewport{nullptr};
    Engine *mWorld{nullptr};
};

#endif // MAINWINDOW_H
