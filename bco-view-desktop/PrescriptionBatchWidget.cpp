#include "PrescriptionBatchWidget.h"
#include "ui_PrescriptionBatchWidget.h"

#include "PrescriptionBatchModel.h"
#include "DbController.h"
#include "PrescriptionBatchDao.h"

#include <QMessageBox>

PrescriptionBatchWidget::PrescriptionBatchWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PrescriptionBatchWidget)
  , mModel(new PrescriptionBatchModel())
{
    ui->setupUi(this);
    connect(ui->load_pushButton, &QPushButton::clicked, this, &PrescriptionBatchWidget::load);
    ui->tableView->setModel(mModel);
}

PrescriptionBatchWidget::~PrescriptionBatchWidget()
{
    delete ui;
}

void PrescriptionBatchWidget::load()
{
    mModel->setModel(std::move(DbController::instance().prescriptionBatchDao.batches()));    
}

void PrescriptionBatchWidget::prescriptionOrderSelected(QString prescriptionOrderTechId, int prescriptionOrderId)
{
//    QMessageBox msgBox;
//    msgBox.setText(QString("Prescriontion batch caught selected prescription order event: %1").arg(prescriptionOrderTechId));
//    msgBox.exec();
    mModel->setModel(std::move(DbController::instance().prescriptionBatchDao.batches(prescriptionOrderId)));
    ui->tableView->setModel(mModel);
}
