#include "PrescriptionOrderWidget.h"
#include "ui_PrescriptionOrderWidget.h"

#include "PrescriptionOrderModel.h"
#include "DbController.h"
#include "FilterWidget.h"
#include "MySortFilterProxyModel.h"

#include <QRegExp>

PrescriptionOrderWidget::PrescriptionOrderWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PrescriptionOrderWidget)
  , mModel(new PrescriptionOrderModel())
  , mFilterWidget(new FilterWidget())
  , mProxyModel(new MySortFilterProxyModel(this))
{
    ui->setupUi(this);
    connect(ui->load_pushButton, &QPushButton::clicked, this, &PrescriptionOrderWidget::load);
    connect(ui->select_pushButton, &QPushButton::clicked, this, &PrescriptionOrderWidget::select);

    ui->filter_horizontalLayout->addWidget(mFilterWidget);    

    ui->tableView->setModel(mProxyModel);

    mProxyModel->setSourceModel(mModel);

    connect(mFilterWidget, &FilterWidget::filterChanged, this, &PrescriptionOrderWidget::textFilterChanged);
    connect(mFilterWidget, &QLineEdit::textChanged,
            this, &PrescriptionOrderWidget::textFilterChanged);
}

PrescriptionOrderWidget::~PrescriptionOrderWidget()
{
    delete ui;
}

void PrescriptionOrderWidget::load()
{    
    mModel->setModel(std::move(DbController::instance().prescriptionOrderDao.orders()));
}

void PrescriptionOrderWidget::select()
{
    QItemSelectionModel* model = ui->tableView->selectionModel();
    QModelIndexList indexes = model->selectedIndexes();
    QModelIndex techIdIndex = mModel->index(indexes.first().row(),1,QModelIndex());
    QModelIndex idIndex = mModel->index(indexes.first().row(),0,QModelIndex());

    QVariant varTechId = mModel->data(techIdIndex, Qt::DisplayRole);
    QString techId = varTechId.toString();

    QVariant varId = mModel->data(idIndex, Qt::DisplayRole);
    int id = varId.toInt();

    if(!techId.isNull() && !techId.isEmpty()){
        emit selected(techId,id);
    }

}

void PrescriptionOrderWidget::textFilterChanged()
{
    QRegExp regExp(mFilterWidget->text(), mFilterWidget->caseSensitivity(),mFilterWidget->patternSyntax());
    mProxyModel->setFilterRegExp(regExp);
}

void PrescriptionOrderWidget::dateFilterChanged()
{

}

