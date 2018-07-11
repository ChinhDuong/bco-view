#include "PrescriptionOrderDao.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>
#include <QSqlQueryModel>

#include "PrescriptionOrder.h"
using namespace std;

PrescriptionOrderDao::PrescriptionOrderDao(QSqlDatabase &db):
    mDb(db)
{

}

unique_ptr<vector<unique_ptr<PrescriptionOrder>>> PrescriptionOrderDao::orders() const
{
    unique_ptr<vector<unique_ptr<PrescriptionOrder>>> list(new vector<unique_ptr<PrescriptionOrder>>());
    if(mDb.isOpen()){
        QSqlQuery query(mDb);
        query.exec("SELECT * FROM PrescriptionOrder");
        while(query.next()) {
            unique_ptr<PrescriptionOrder> item(
                        new PrescriptionOrder(
                            query.value("id").toInt(),
                            query.value("techid").toString(),
                            query.value("orderNumber").toString(),
                            query.value("dateCreated").toDateTime(),
                            query.value("dateDeleted").toDateTime(),
                            query.value("reportNumber").toString(),
                            query.value("companyLogo").toString(),
                            query.value("templateImage1").toString(),
                            query.value("templateImage2").toString(),
                            query.value("templateImage3").toString(),
                            query.value("templateImage4").toString(),
                            query.value("printMethodOnScanTray").toString()
                            ));

            list->push_back(move(item));
        }
    }



    return list;
}
