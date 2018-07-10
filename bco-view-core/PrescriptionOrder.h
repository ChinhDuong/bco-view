#ifndef PRESCRIPTIONORDER_H
#define PRESCRIPTIONORDER_H
#include <QString>

class PrescriptionOrder
{
public:
    PrescriptionOrder(int id, QString techId, QString orderNumber);
    int id() const;
    QString techId() const;
    QString orderNumber() const;
private:
    int mId;
    QString mTechId;
    QString mOrderNumber;


};

#endif // PRESCRIPTIONORDER_H
