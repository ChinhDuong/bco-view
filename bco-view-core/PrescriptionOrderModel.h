#ifndef PRESCRIPTIONORDERMODEL_H
#define PRESCRIPTIONORDERMODEL_H

#include <vector>
#include <memory>

#include "bco-view-core_global.h"

#include <QAbstractTableModel>

#include "PrescriptionOrder.h"

class BCOVIEWCORESHARED_EXPORT PrescriptionOrderModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    PrescriptionOrderModel(QObject* parent = 0 );

private:
    bool isIndexValid(const QModelIndex& index) const;
private:
    std::unique_ptr<std::vector<std::unique_ptr<PrescriptionOrder>>> mOrders;

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    void setModel(std::unique_ptr<std::vector<std::unique_ptr<PrescriptionOrder>>> orders);
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;



};

#endif // PRESCRIPTIONORDERMODEL_H
