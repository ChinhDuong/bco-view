#ifndef MYSORTFILTERPROXYMODEL_H
#define MYSORTFILTERPROXYMODEL_H

#include <QSortFilterProxyModel>
#include "bco-view-core_global.h"
#include <QDate>
class BCOVIEWCORESHARED_EXPORT MySortFilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    MySortFilterProxyModel(QObject *parent = 0);

    QDate filterMinimumDate() const { return minDate; }
    void setFilterMinimumDate(const QDate &date);

    QDate filterMaximumDate() const { return maxDate; }
    void setFilterMaximumDate(const QDate &date);


protected:
//    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;
//    bool lessThan(const QModelIndex &left, const QModelIndex &right) const override;

private:
    bool dateInRange(const QDate &date) const;

    QDate minDate;
    QDate maxDate;
};

#endif // MYSORTFILTERPROXYMODEL_H
