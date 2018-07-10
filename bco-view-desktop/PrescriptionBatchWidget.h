#ifndef PRESCRIPTIONBATCHWIDGET_H
#define PRESCRIPTIONBATCHWIDGET_H

#include <QWidget>

class PrescriptionBatchModel;
namespace Ui {
class PrescriptionBatchWidget;
}

class PrescriptionBatchWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PrescriptionBatchWidget(QWidget *parent = 0);
    ~PrescriptionBatchWidget();

private:
    Ui::PrescriptionBatchWidget *ui;
    PrescriptionBatchModel* mModel;
public slots:
    void load();
    void prescriptionOrderSelected(QString prescriptionOrderTechId, int prescriptionOrderId);
};

#endif // PRESCRIPTIONBATCHWIDGET_H
