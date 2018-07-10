#ifndef PRESCRIPTIONBATCHMODEL_H
#define PRESCRIPTIONBATCHMODEL_H

#include "bco-view-core_global.h"
#include <QAbstractTableModel>

#include <vector>
#include <memory>

#include "PrescriptionBatch.h"

class BCOVIEWCORESHARED_EXPORT PrescriptionBatchModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    PrescriptionBatchModel(QObject* parent = 0 );
signals:

public slots:

private:
    bool isIndexValid(const QModelIndex& index) const;
private:
    std::unique_ptr<std::vector<std::unique_ptr<PrescriptionBatch>>> mBatches;

public:
    int rowCount(const QModelIndex &parent ) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    void setModel(std::unique_ptr<std::vector<std::unique_ptr<PrescriptionBatch>>> batches);   
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
};

#endif // PRESCRIPTIONBATCHMODEL_H
