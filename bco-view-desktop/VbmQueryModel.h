#ifndef VBMQUERYMODEL_H
#define VBMQUERYMODEL_H

#include <QAbstractListModel>
#include <memory>
#include <vector>

class VbmQueryInfo;

class VbmQueryModel: public QAbstractTableModel {
  public:
    VbmQueryModel();

    // QAbstractItemModel interface
  public:
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role) const override;
    void setModel(std::unique_ptr<std::vector<std::unique_ptr<VbmQueryInfo>>> dataSource);
    int columnCount(const QModelIndex& parent) const override;
  private:
    bool isIndexValid(const QModelIndex& index) const;
  private:
    std::unique_ptr<std::vector<std::unique_ptr<VbmQueryInfo>>> m_DataSource;


};

#endif // VBMQUERYMODEL_H
