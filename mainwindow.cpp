#include <QDebug>
#include <QDir>
#include <QCamera>
#include <QActionGroup>
#include <QByteArray>

#include "mainwindow.h"
#include "ui_login.h"
#include "ui_main.h"



MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    QWidget *loginWidget = new QWidget();
    loginUi = new Ui::loginWindow();
    loginUi->setupUi(loginWidget);

    connect(loginUi->pushButton, SIGNAL(clicked()), this, SLOT(openForm()));
    this->setCentralWidget(loginWidget);

}

MainWindow::~MainWindow()
{
    delete loginUi;
}

void MainWindow::openForm() {
    QString formId = loginUi->lineEdit->text();

    QWidget *mainWidget = new QWidget();
    mainUi = new Ui::mainWindow();
    mainUi->setupUi(mainWidget);

    mainUi->webView->setUrl("file://" + QDir::currentPath() + "/lomake_placeholder.html");

    QPalette palette = QPalette();
    palette.setColor(QPalette::Background, Qt::red);
    mainUi->frame->setPalette(palette);


    this->setCentralWidget(mainWidget);
    connect(mainUi->stopButton, SIGNAL(clicked()), this, SLOT(closeForm()));
    connect(mainUi->takepictureButton, SIGNAL(clicked()), this, SLOT(openPicturechangeWindow()));

}

QWidget *oldform;

void MainWindow::closeForm() {
    QWidget *loginWidget = new QWidget();
    loginUi = new Ui::loginWindow();
    loginUi->setupUi(loginWidget);

    this->setCentralWidget(loginWidget);
    connect(loginUi->pushButton, SIGNAL(clicked()), this, SLOT(openForm()));
}

void MainWindow::openPicturechangeWindow() {
    //wview = mainUi->webView;
    //this->centralWidget()->layout()->removeWidget(mainUi->webView);

    QWidget *takepictureWidget = new QWidget();
    takepictureUi = new Ui::takepictureWindow();
    takepictureUi->setupUi(takepictureWidget);

    oldform = this->centralWidget();
    this->centralWidget()->setParent(0);
    this->setCentralWidget(takepictureWidget);

    connect(takepictureUi->cancelButton, SIGNAL(clicked()), this, SLOT(reloadForm()));

    QCamera *camera;
    QActionGroup *videoDevicesGroup = new QActionGroup(this);
    QByteArray cameraDevice;

    foreach(const QByteArray &deviceName, QCamera::availableDevices()) {
        QString description = camera->deviceDescription(deviceName);
        QAction *videoDeviceAction = new QAction(description, videoDevicesGroup);
        videoDeviceAction->setCheckable(true);
        videoDeviceAction->setData(QVariant(deviceName));
        if (cameraDevice.isEmpty()) {
            cameraDevice = deviceName;
            videoDeviceAction->setChecked(true);
            camera = new QCamera(cameraDevice);
        }
        qDebug() << deviceName;
    }
    camera->setViewfinder(takepictureUi->viewfinder);
    camera->start();
}

void MainWindow::reloadForm() {
    QWidget *mainWidget = new QWidget();
    mainUi = new Ui::mainWindow();
    mainUi->setupUi(mainWidget);

    //wview = new QWebView();
    //this->setCentralWidget(mainWidget);
    //((QVBoxLayout*)this->centralWidget()->layout()->itemAt(1))->removeWidget(mainUi->webView);
    //((QVBoxLayout*)this->centralWidget()->layout()->itemAt(1))->addWidget(wview);

    /*mainUi->verticalLayout->removeWidget(mainUi->webView);
    mainUi->webView->close();
    mainUi->webView = wview;
    mainUi->verticalLayout->addWidget(mainUi->webView,1);
    mainUi->verticalLayout->update();
    mainUi->horizontalLayout->update();*/
    this->setCentralWidget(oldform);

    connect(mainUi->stopButton, SIGNAL(clicked()), this, SLOT(closeForm()));
    connect(mainUi->takepictureButton, SIGNAL(clicked()), this, SLOT(openPicturechangeWindow()));
}
