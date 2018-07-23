#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "DbController.h"

namespace Ui {
class MainWindow;
}
class VbmTableWidget;
class VbmQueryWidget;
//class DbController;
class MainWindow : public QMainWindow {
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
    void addView();
  signals:
    void connectToServer(QString);
    void disconnectFromServer();
  private:
    QJsonDocument loadConnections();
  private:
    Ui::MainWindow* ui;
    DbController*   db_controller;
    QThread*        db_thread;
    QVector<VbmTableWidget*> mTables;
    QVector<VbmQueryWidget*> mQueries;
    int mColumnCount;

};
#endif // MAINWINDOW_H
