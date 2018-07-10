#include "PrescriptionOrder.h"

PrescriptionOrder::PrescriptionOrder(int id, QString techId, QString orderNumber):
    mId(id),
    mTechId(techId),
    mOrderNumber(orderNumber)
{

}

int PrescriptionOrder::id() const
{
    return mId;
}

QString PrescriptionOrder::techId() const
{
    return mTechId;
}

QString PrescriptionOrder::orderNumber() const
{
    return mOrderNumber;
}
