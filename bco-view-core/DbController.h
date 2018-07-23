#ifndef DBCONTROLLER_H
#define DBCONTROLLER_H

#include "bco-view-core_global.h"

#include <QString>
#include <QtSql>

class BCOVIEWCORESHARED_EXPORT DbController: public QObject {
    Q_OBJECT
  public:
    static DbController& instance();
    ~DbController();
    bool checkIfConnected();
  protected:
    DbController(QObject* parent = 0);
    DbController& operator=(const DbController& rhs);
  public slots:
    void connectToServerRequested(QString);
    void disconnectFromServerRequested();
    void selectTableRequested(QString table);
  signals:
    void serverConnected();
    void serverErrorWithConnection(QString);
    void serverDisconnected();
    void tableSelected(QSqlQueryModel*);
    void gotTablesNames(QStringList tableNames);
  private:
    bool connectToServerMSSQL(QString);
    void disconnectFromServer();
    QSqlError getLastError();

    std::unique_ptr<QSqlDatabase> mDatabase;
  public :
    QSqlQueryModel* selectTable(QString query);
    QStringList getTableNames();


};
#endif // DBCONTROLLER_H
