#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QOpenGLContext>
#include <QSurfaceFormat>
#include <QtGlobal>
#include <QDebug>
#include <QMessageBox>
#include "viewport.h"
#include "engine.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    init();
    connectSignalsSlots();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init()
{
    QSurfaceFormat format;
    format.setVersion(4, 1);
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setRenderableType(QSurfaceFormat::OpenGL);
    format.setSamples(4);                                   // Set the number of samples used for multisampling
    format.setDepthBufferSize(24);                          // The example rendering will need a depth buffer.
    format.setOption(QSurfaceFormat::DebugContext);         //Should activate OpenGL debug Context used in RenderWindow::startOpenGLDebugger()

    mViewport = new Viewport(format);
    Q_ASSERT_X(mViewport, "MainWindow::init()", "Failed to create viewport");
    mViewportWidget = QWidget::createWindowContainer(mViewport);
    ui->viewport->addWidget(mViewportWidget);
    mViewportWidget->setFocus();

    // Settings
    setWindowTitle(QString("Frolt Engine"));
//    setCursor(Qt::CrossCursor);
//    showFullScreen();
}

void MainWindow::connectSignalsSlots()
{
    connect(ui->realExit, SIGNAL(clicked()), this, SLOT(close()));
    connect(mViewport, SIGNAL(ready()), this, SLOT(viewportReady()));
}

void MainWindow::viewportReady()
{
    mEngine = new Engine(mViewport);
}

void MainWindow::on_messageButton_clicked()
{
    // TODO testing stuff
    auto reply = QMessageBox::question(this, "A message title", "here is the message!",
                                       QMessageBox::StandardButton::Save |
                                       QMessageBox::StandardButton::Cancel |
                                       QMessageBox::StandardButton::Discard,
                                       QMessageBox::StandardButton::Cancel);
    if (reply == QMessageBox::Discard) {
        QApplication::quit();
    } else {
        qDebug() << "lal";
    }
}
void MainWindow::on_Exit_triggered()
{
    QApplication::quit();
}
