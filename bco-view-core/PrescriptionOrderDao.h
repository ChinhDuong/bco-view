#ifndef PRESCRIPTIONORDERREPOSITORY_H
#define PRESCRIPTIONORDERREPOSITORY_H

#include <vector>
#include <memory>
#include "bco-view-core_global.h"

class PrescriptionOrder;
class QSqlDatabase;
class BCOVIEWCORESHARED_EXPORT PrescriptionOrderDao
{
public:
    PrescriptionOrderDao(QSqlDatabase& db);
    std::unique_ptr<std::vector<std::unique_ptr<PrescriptionOrder>>> orders() const;

private:
    QSqlDatabase& mDb;
};

#endif // PRESCRIPTIONORDERREPOSITORY_H
