#ifndef DBCONTROLLER_H
#define DBCONTROLLER_H

#include "bco-view-core_global.h"

#include <QString>
#include <QtSql>
#include "PrescriptionBatchDao.h"
#include "PrescriptionOrderDao.h"

class BCOVIEWCORESHARED_EXPORT DbController: public QObject
{    
    Q_OBJECT
public:
    static DbController& instance();
    ~DbController();
    bool checkIfConnected();
protected:
    DbController(QObject* parent=0);
    DbController& operator=(const DbController& rhs);
public slots:
    void connectToServerRequested(QString);
    void disconnectFromServerRequested();

signals:
    void serverConnected();
    void serverErrorWithConnection(QString);
    void serverDisconnected();

private:
    bool connectToServerMSSQL(QString);
    void disconnectFromServer();    
    QSqlError       getLastError();

    std::unique_ptr<QSqlDatabase> mDatabase;
public:
    PrescriptionOrderDao prescriptionOrderDao;
    PrescriptionBatchDao prescriptionBatchDao;
};
#endif // DBCONTROLLER_H
