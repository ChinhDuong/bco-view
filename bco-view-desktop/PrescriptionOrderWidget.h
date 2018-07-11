#ifndef PRESCRIPTIONORDERWIDGET_H
#define PRESCRIPTIONORDERWIDGET_H

#include <QWidget>

class FilterWidget;
namespace Ui {
class PrescriptionOrderWidget;
}
class PrescriptionOrderModel;
class MySortFilterProxyModel;

class PrescriptionOrderWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PrescriptionOrderWidget(QWidget *parent = 0);
    ~PrescriptionOrderWidget();

private:
    Ui::PrescriptionOrderWidget *ui;
    PrescriptionOrderModel* mModel;
    FilterWidget *mFilterWidget;
    MySortFilterProxyModel* mProxyModel;
public slots:
    void load();
    void select();
    void textFilterChanged();
    void dateFilterChanged();
signals:
    void selected(QString prescriptionOrderTechId, int prescriptionOrderId);
};

#endif // PRESCRIPTIONORDERWIDGET_H
