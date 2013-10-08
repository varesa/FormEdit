#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "ui_main.h"
#include "ui_login.h"
#include "ui_takepicture.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::loginWindow *loginUi;
    Ui::mainWindow  *mainUi;
    Ui::takepictureWindow *takepictureUi;

public slots:
    void openForm();
    void closeForm();
    void openPicturechangeWindow();
    void reloadForm();
};

#endif // MAINWINDOW_H
