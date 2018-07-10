#ifndef PRESCRIPTIONORDERWIDGET_H
#define PRESCRIPTIONORDERWIDGET_H

#include <QWidget>


namespace Ui {
class PrescriptionOrderWidget;
}
class PrescriptionOrderModel;
class PrescriptionOrderWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PrescriptionOrderWidget(QWidget *parent = 0);
    ~PrescriptionOrderWidget();

private:
    Ui::PrescriptionOrderWidget *ui;
    PrescriptionOrderModel* mModel;
public slots:
    void load();
    void select();
signals:
    void selected(QString prescriptionOrderTechId, int prescriptionOrderId);
};

#endif // PRESCRIPTIONORDERWIDGET_H
