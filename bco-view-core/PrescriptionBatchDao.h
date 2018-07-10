#ifndef PRESCRIPTIONBATCHDAO_H
#define PRESCRIPTIONBATCHDAO_H
#include "bco-view-core_global.h"

#include <vector>
#include <memory>


class PrescriptionBatch;
class QSqlDatabase;


class BCOVIEWCORESHARED_EXPORT PrescriptionBatchDao
{
public:
    PrescriptionBatchDao(QSqlDatabase& db);
    std::unique_ptr<std::vector<std::unique_ptr<PrescriptionBatch>>> batches() const;
    std::unique_ptr<std::vector<std::unique_ptr<PrescriptionBatch>>> batches(int prescriptionOrderId) const;
private:
    QSqlDatabase& mDb;
};

#endif // PRESCRIPTIONBATCHDAO_H
