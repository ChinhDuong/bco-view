#include "PrescriptionBatchDao.h"
#include "PrescriptionBatch.h"


#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>
#include <QSqlQueryModel>

using namespace std;

PrescriptionBatchDao::PrescriptionBatchDao(QSqlDatabase &db):
    mDb(db)
{

}

std::unique_ptr<std::vector<std::unique_ptr<PrescriptionBatch> > > PrescriptionBatchDao::batches() const
{
    unique_ptr<vector<unique_ptr<PrescriptionBatch>>> list(new vector<unique_ptr<PrescriptionBatch>>());
    if(!mDb.isOpen()){
        mDb.open();
    }

    QSqlQuery query(mDb);
    query.exec("SELECT * FROM PrescriptionBatch");
    while(query.next()) {
        unique_ptr<PrescriptionBatch> item(
                    new PrescriptionBatch(
                        query.value("id").toInt(),
                        query.value("techid").toString(),
                        query.value("batchNumber").toString(),
                        query.value("dateCreated").toDateTime(),
                        query.value("dateDeleted").toDateTime()
                        ));

        list->push_back(move(item));
    }

    return list;
}

std::unique_ptr<std::vector<std::unique_ptr<PrescriptionBatch> > > PrescriptionBatchDao::batches(int prescriptionOrderId) const
{
    unique_ptr<vector<unique_ptr<PrescriptionBatch>>> list(new vector<unique_ptr<PrescriptionBatch>>());
    if(!mDb.isOpen()){
        mDb.open();
    }

    QSqlQuery query(mDb);
    query.exec(QString("SELECT * FROM PrescriptionBatch WHERE FK_PrescriptionOrder = %1 ").arg(prescriptionOrderId));
    while(query.next()) {
        unique_ptr<PrescriptionBatch> item(
                    new PrescriptionBatch(
                        query.value("id").toInt(),
                        query.value("techid").toString(),
                        query.value("batchNumber").toString(),
                        query.value("dateCreated").toDateTime(),
                        query.value("dateDeleted").toDateTime()
                        ));

        list->push_back(move(item));
    }

    return list;
}
