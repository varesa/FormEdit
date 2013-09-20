#include <QDebug>

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
    qDebug() << formId;

    QWidget *mainWidget = new QWidget();
    mainUi = new Ui::mainWindow();
    mainUi->setupUi(mainWidget);

    mainUi->webView->setUrl(QUrl("http://www.google.fi/"));

    QPalette palette = QPalette();
    palette.setColor(QPalette::Background, Qt::red);
    mainUi->frame->setPalette(palette);


    this->setCentralWidget(mainWidget);

    connect(mainUi->stopButton, SIGNAL(clicked()), this, SLOT(closeForm()));

}

void MainWindow::closeForm() {
    QWidget *loginWidget = new QWidget();
    loginUi = new Ui::loginWindow();
    loginUi->setupUi(loginWidget);

    this->setCentralWidget(loginWidget);
    connect(loginUi->pushButton, SIGNAL(clicked()), this, SLOT(openForm()));
}
