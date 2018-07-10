#ifndef PRESCRIPTIONBATCH_H
#define PRESCRIPTIONBATCH_H

#include <QString>
#include <QDateTime>

class PrescriptionBatch
{
public:
    PrescriptionBatch(int id, QString techId, QString batchNumber, QDateTime dateCreated, QDateTime dateDeleted);
    int id() const;
    QString techId() const;
    QString batchNumber() const;
    QDateTime dateCreated() const;
    QDateTime dateDeleted() const;
private:
    int mId;
    QString mTechId;
    QString mBatchNumber;
    QDateTime mDateCreated;
    QDateTime mDateDeleted;
};

#endif // PRESCRIPTIONBATCH_H
