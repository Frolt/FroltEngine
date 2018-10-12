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
    delete mViewport;
}

void MainWindow::init()
{
    // TODO snakk med Ole
    QSurfaceFormat format;
    format.setVersion(4, 1);
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setRenderableType(QSurfaceFormat::OpenGL);
    format.setSamples(4);
    format.setDepthBufferSize(24);
    format.setOption(QSurfaceFormat::DebugContext);
    format.setSwapInterval(0); // Distable Vsync

    mViewport = new Viewport(format, this);
    mViewportWidget = QWidget::createWindowContainer(mViewport);
    ui->viewport->addWidget(mViewportWidget);
    mViewportWidget->setFocus();

    // Settings
    setWindowTitle(QString("Frolt Engine"));
//    showFullScreen();
}

void MainWindow::connectSignalsSlots()
{
    connect(ui->realExit, SIGNAL(clicked()), this, SLOT(close()));
    connect(mViewport, SIGNAL(ready()), this, SLOT(viewportReady()));
    connect(mViewport, SIGNAL(FPS()), this, SLOT(showFPS()));
}

void MainWindow::viewportReady()
{
    mEngine = new Engine(mViewport);
    QOpenGLContext *context = QOpenGLContext::currentContext();
    Q_ASSERT(context);
}

void MainWindow::on_messageButton_clicked()
{
    auto reply = QMessageBox::question(this, "A message title", "here is the message!",
                                       QMessageBox::StandardButton::Save |
                                       QMessageBox::StandardButton::Cancel |
                                       QMessageBox::StandardButton::Discard,
                                       QMessageBox::StandardButton::Cancel);
    if (reply == QMessageBox::Discard) {
        QApplication::quit();
    } else {
        qDebug() << "dust";
    }
}
void MainWindow::on_Exit_triggered()
{
    QApplication::quit();
}

void MainWindow::showFPS()
{
    static int frameCount{0};
    static float secCount{0};
    frameCount++;
    secCount += mEngine->mDeltaTime;
    statusBar()->showMessage(" FPS: " + QString::number(static_cast<int>(frameCount / secCount)));
    if (secCount > 1.0f) {
        secCount = 0.0f;
        frameCount = 0;
    }
}
