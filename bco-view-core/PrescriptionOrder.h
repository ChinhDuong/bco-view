#ifndef PRESCRIPTIONORDER_H
#define PRESCRIPTIONORDER_H
#include <QString>
#include <QDateTime>

class PrescriptionOrder
{
public:
    PrescriptionOrder(int id, QString techId, QString orderNumber,QDateTime dateCreated
                      , QDateTime dateDeleted, QString reportNumber, QString companyLogo
                      , QString templateImage1, QString templateImage2, QString templateImage3
                      , QString templateImage4, QString printMethodOnScanTray);
    int id() const;
    QString techId() const;
    QString orderNumber() const;
    QDateTime dateCreated() const;
    QDateTime dateDeleted() const;
    QString reportNumber() const;
    QString comanyLogo() const;
    QString templateImage1() const;
    QString templateImage2() const;
    QString templateImage3() const;
    QString templateImage4() const;
    QString printMethodOnScanTray() const;

private:
    int mId;
    QString mTechId;
    QString mOrderNumber;
    QDateTime mDateCreated;
    QDateTime mDateDeleted;
    QString mReportNumber;
    QString mCompanyLogo;
    QString mTemplateImage1;
    QString mTemplateImage2;
    QString mTemplateImage3;
    QString mTemplateImage4;
    QString mPrintMethodOnScanTray;

};

#endif // PRESCRIPTIONORDER_H
