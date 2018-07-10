#include "DbController.h"


DbController &DbController::instance()
{
    static DbController singleton;
    return singleton;
}

DbController::~DbController()
{
    if (mDatabase->isOpen())
    {
        mDatabase->close();
    }
}

bool DbController::checkIfConnected()
{
    return mDatabase->isOpen();
}

DbController::DbController(QObject* parent):QObject(parent),
    mDatabase(new QSqlDatabase(QSqlDatabase::addDatabase("QODBC", "qt-sql-connection"))),
    prescriptionOrderDao(*mDatabase),
    prescriptionBatchDao(*mDatabase)
{

}

void DbController::connectToServerRequested(QString connectionString)
{

    bool connection_succesfull;

    connection_succesfull = connectToServerMSSQL(connectionString);
    if (connection_succesfull)
        emit serverConnected();
    else
        emit serverErrorWithConnection(getLastError().driverText());
}


void DbController::disconnectFromServerRequested()
{
    disconnectFromServer();

    emit serverDisconnected();
}

bool DbController::connectToServerMSSQL(QString connectionString)
{
    mDatabase->setDatabaseName(connectionString);
    return mDatabase->open();
}

void DbController::disconnectFromServer()
{
    mDatabase->close();
}

QSqlError DbController::getLastError()
{
    return mDatabase->lastError();
}
