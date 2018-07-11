#include "PrescriptionOrder.h"


PrescriptionOrder::PrescriptionOrder(int id, QString techId, QString orderNumber, QDateTime dateCreated, QDateTime dateDeleted, QString reportNumber, QString companyLogo, QString templateImage1, QString templateImage2, QString templateImage3, QString templateImage4, QString printMethodOnScanTray):
    mId(id),
    mTechId(techId),
    mOrderNumber(orderNumber),
    mDateCreated(dateCreated),
    mDateDeleted(dateDeleted),
    mReportNumber(reportNumber),
    mCompanyLogo(companyLogo),
    mTemplateImage1(templateImage1),
    mTemplateImage2(templateImage2),
    mTemplateImage3(templateImage3),
    mTemplateImage4(templateImage4),
    mPrintMethodOnScanTray(printMethodOnScanTray)
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

QDateTime PrescriptionOrder::dateCreated() const
{
    return mDateCreated;
}

QDateTime PrescriptionOrder::dateDeleted() const
{
    return mDateDeleted;
}

QString PrescriptionOrder::reportNumber() const
{
    return mReportNumber;
}

QString PrescriptionOrder::comanyLogo() const
{
    return mCompanyLogo;
}

QString PrescriptionOrder::templateImage1() const
{
    return mTemplateImage1;
}

QString PrescriptionOrder::templateImage2() const
{
    return mTemplateImage2;
}

QString PrescriptionOrder::templateImage3() const
{
    return mTemplateImage3;
}

QString PrescriptionOrder::templateImage4() const
{
    return mTemplateImage4;
}

QString PrescriptionOrder::printMethodOnScanTray() const
{
    return mPrintMethodOnScanTray;
}
