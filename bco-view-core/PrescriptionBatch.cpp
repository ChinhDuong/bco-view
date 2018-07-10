#include "PrescriptionBatch.h"

PrescriptionBatch::PrescriptionBatch(int id, QString techId, QString batchNumber, QDateTime dateCreated, QDateTime dateDeleted):
    mId(id),mTechId(techId),mBatchNumber(batchNumber),mDateCreated(dateCreated)
  ,mDateDeleted(dateDeleted)
{

}

int PrescriptionBatch::id() const
{
    return mId;
}

QString PrescriptionBatch::techId() const
{
    return mTechId;
}

QString PrescriptionBatch::batchNumber() const
{
    return mBatchNumber;
}

QDateTime PrescriptionBatch::dateCreated() const
{
    return mDateCreated;
}

QDateTime PrescriptionBatch::dateDeleted() const
{
    return mDateDeleted;
}
