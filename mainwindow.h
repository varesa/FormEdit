#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "ui_main.h"
#include "ui_login.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::loginWindow *loginUi;
    Ui::mainWindow  *mainUi;

public slots:
    void openForm();
    void closeForm();
};

#endif // MAINWINDOW_H
