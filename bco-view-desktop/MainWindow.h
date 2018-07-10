#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "DbController.h"

namespace Ui {
class MainWindow;
}
//class DbController;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
//    explicit MainWindow(QWidget *parent = 0);
    explicit MainWindow(QWidget* parent, DbController* dbc, QThread* dbt);
    ~MainWindow();
public slots:
    void connectToServerRequested();
    void disconnectFromServerRequested();
    void serverConnected();
    void serverDisconnected();
    void serverErrorWithConnection(QString);
signals:
    void connectToServer(QString);
    void disconnectFromServer();
private:
    Ui::MainWindow *ui;
    DbController*   db_controller;
    QThread*        db_thread;

};
#endif // MAINWINDOW_H
