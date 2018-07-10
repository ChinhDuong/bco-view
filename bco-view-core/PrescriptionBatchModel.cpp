#include "PrescriptionBatchModel.h"

PrescriptionBatchModel::PrescriptionBatchModel(QObject *parent):
    QAbstractTableModel(parent)
{

}

int PrescriptionBatchModel::rowCount(const QModelIndex &parent ) const
{
    Q_UNUSED(parent);
    return mBatches->size();
}

int PrescriptionBatchModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 5;
}

QVariant PrescriptionBatchModel::data(const QModelIndex &index, int role) const
{
    if (!isIndexValid(index)) {
        return QVariant();
    }
    const PrescriptionBatch& item = *mBatches->at(index.row());
    if(role == Qt::DisplayRole){
        switch (index.column())
        {
        case 0:
            return item.id();
        case 1:
            return item.techId();
        case 2:
            return item.batchNumber();
        case 3:
            return item.dateCreated();
        case 4:
            return item.dateDeleted();
        default:
            return QVariant();
        }
    }else{
        return QVariant();
    }
}

void PrescriptionBatchModel::setModel(std::unique_ptr<std::vector<std::unique_ptr<PrescriptionBatch>>> batches)
{
    beginResetModel();
    mBatches = move(batches);
    endResetModel();
}

QVariant PrescriptionBatchModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role != Qt::DisplayRole){
        return QVariant();
    }

    if(orientation == Qt::Horizontal){
        switch (section){
        case 0:
            return tr("Id");
        case 1:
            return tr("Tech id");
        case 2:
            return tr("Batch number");
        case 3:
            return tr("Date created");
        case 4:
            return tr("Date deleted");
        default:
            return QVariant();
        }
    }
    return QVariant();
}

bool PrescriptionBatchModel::isIndexValid(const QModelIndex &index) const
{
    if (index.row() < 0
            || index.row() >= rowCount(QModelIndex())
            || !index.isValid()) {
        return false;
    }
    return true;
}
