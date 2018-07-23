#include "VbmQueryModel.h"
#include "VbmQueryInfo.h"
using namespace std;

VbmQueryModel::VbmQueryModel()
{

}

int VbmQueryModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent);
    return m_DataSource->size();
}

QVariant VbmQueryModel::data(const QModelIndex& index, int role) const
{
    if (!isIndexValid(index)) {
        return QVariant();
    }

    const VbmQueryInfo& info = *m_DataSource->at(index.row());

    if (role == Qt::DisplayRole) {
        switch (index.column()) {
            case 0:
                return info.description();

            case 1:
                return info.query();

            default:
                return QVariant();
        }
    } else {

        return QVariant();
    }


}

void VbmQueryModel::setModel(unique_ptr<vector<unique_ptr<VbmQueryInfo>>> dataSource)
{
    this->beginResetModel();
    m_DataSource = move(dataSource);
    this->endResetModel();
}

int VbmQueryModel::columnCount(const QModelIndex& parent) const
{
    return 2;
}
bool VbmQueryModel::isIndexValid(const QModelIndex& index) const
{
    if (index.row() < 0
            || index.row() >= rowCount()
            || !index.isValid()) {
        return false;
    }

    return true;
}
