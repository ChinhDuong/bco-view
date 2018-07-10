#include "PrescriptionOrderModel.h"

#include "DbController.h"
#include "PrescriptionOrder.h"

using namespace std;
PrescriptionOrderModel::PrescriptionOrderModel(QObject *parent):QAbstractTableModel(parent),
  mOrders(new vector<unique_ptr<PrescriptionOrder>>())
{

}

int PrescriptionOrderModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return mOrders->size();
}

int PrescriptionOrderModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 3;
}

QVariant PrescriptionOrderModel::data(const QModelIndex &index, int role) const
{
    if (!isIndexValid(index)) {
        return QVariant();
    }
    const PrescriptionOrder& item = *mOrders->at(index.row());
    if(role == Qt::DisplayRole){
        switch (index.column())
        {
        case 0:

            return item.id();
        case 1:
            return item.techId();
        case 2:
            return item.orderNumber();
        default:
            return QVariant();
        }
    }else{
        return QVariant();
    }

}

void PrescriptionOrderModel::setModel(unique_ptr<vector<unique_ptr<PrescriptionOrder>>> orders)
{
    beginResetModel();
    mOrders = move(orders);
    endResetModel();
}

QVariant PrescriptionOrderModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
             return QVariant();

         if (orientation == Qt::Horizontal) {
             switch (section) {
                 case 0:
                     return tr("Id");
                 case 1:
                     return tr("Tech id");
                 case 2:
                    return tr("Order number");
                 default:
                     return QVariant();
             }
         }
         return QVariant();
}


bool PrescriptionOrderModel::isIndexValid(const QModelIndex &index) const
{
    if (index.row() < 0
            || index.row() >= rowCount(QModelIndex())
            || !index.isValid()) {
        return false;
    }
    return true;
}
